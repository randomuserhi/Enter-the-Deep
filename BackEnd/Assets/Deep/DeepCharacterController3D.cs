using Deep.Math;
using UnityEngine;

// TODO(randomuserhi) => Manage flipping of gravity properly

namespace Deep {
    [RequireComponent(typeof(CapsuleCollider))]
    [RequireComponent(typeof(Rigidbody))]
    public class DeepCharacterController3D : MonoBehaviour {
        private Rigidbody rb;
        private new CapsuleCollider collider;

        // Accessors
        public bool Grounded {
            get => groundedState == GroundedState.Grounded;
        }
        public bool GroundedTransition {
            get => groundedTransition;
        }
        public bool Slip {
            get => groundedState == GroundedState.Slip;
        }
        public bool SlipTransition {
            get => slipTransition;
        }
        public bool Airborne {
            get => groundedState == GroundedState.Airborne;
            set {
                if (value) {
                    groundedState = GroundedState.Airborne;
                } else {
                    groundedState = GroundedState.Grounded;
                }
            }
        }
        public bool AirborneTransition {
            get => airborneTransition;
        }

        public Vector3 SurfaceNormal {
            get => surfaceNormal;
        }

        // Settings
        public float height = 2f;
        public float radius = 0.5f;

        public float gravity = 10f;

        private LayerMask surfaceLayerMask = Physics.AllLayers;

        private float hoverHeight = 0.25f;
        private float stickyHeight = 1f;
        private float maxSlopeCosAngle = 0.5f;

        // TODO(randomuserhi): Refactor hover spring -> notably SecondOrderDynamics class
        private SecondOrderDynamics hoverSpring = new SecondOrderDynamics(5f, 0.5f, 0f, 0f);

        // State
        private Vector3 surfaceNormal = Vector3.up;

        private GroundedState groundedState = GroundedState.Airborne;
        private bool prevGrounded = false;
        private bool groundedTransition = false;
        private bool prevSlip = false;
        private bool slipTransition = false;
        private bool prevAirborne = false;
        private bool airborneTransition = false;

        private RaycastHit hit;
        private bool sticky = false;
        private bool prevSticky = false;
        private bool stickyTransition = false;

        private Vector3 bottom = Vector3.zero;
        public Vector3 Bottom { get => bottom; }
        public Vector3 Center { get => bottom - new Vector3(0, height, 0); }

        private void Start() {
            rb = GetComponent<Rigidbody>();
            rb.constraints = RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;

            collider = GetComponent<CapsuleCollider>();
        }

        private enum GroundedState {
            Airborne,
            Grounded,
            Slip
        }

        private enum StickyHitType {
            None,
            Sticky,
            Slip
        }

        private StickyHitType StickySlipCheck(RaycastHit hit) {
            if (hit.distance < stickyHeight && Vector3.Dot(Vector2.down, hit.normal) < 0) {
                if (Vector3.Dot(Vector2.up, hit.normal) >= maxSlopeCosAngle) {
                    return StickyHitType.Sticky;
                } else {
                    return StickyHitType.Slip;
                }
            }
            return StickyHitType.None;
        }

        private StickyHitType WillBeStickyHit(out RaycastHit hit) {
            // Will we be sticky in the future?
            Vector3 dir = Vector3.down;
            if (new Vector2(rb.velocity.x, rb.velocity.z) != Vector2.zero && rb.velocity.y < 0) {
                dir = rb.velocity.normalized;
            }
            Vector3 halfExtents = new Vector3(radius, 0.01f / 2f, radius);
            if (Physics.BoxCast(rb.position, halfExtents, dir, out hit, rb.rotation, Mathf.Infinity, surfaceLayerMask)) {
                hit.distance = Mathf.Abs(rb.position.y - hit.point.y); // NOTE(randomuserhi): We only care about height above the ground, so transform distance to just represent that.
                return StickySlipCheck(hit);
            }
            return StickyHitType.None;
        }

        private StickyHitType StickyHit(out RaycastHit hit) {
            Vector3 halfExtents = new Vector3(radius, 0.01f / 2f, radius);
            if (Physics.BoxCast(rb.position, halfExtents, Vector3.down, out hit, rb.rotation, stickyHeight, surfaceLayerMask)) {
                return StickySlipCheck(hit);
            }
            return StickyHitType.None;
        }

        private void HandleGrounded() {
            Vector3 gravity = Vector3.down * this.gravity;
            if (gravity == Vector3.zero) {
                groundedState = GroundedState.Airborne;
                prevGrounded = false;
                groundedTransition = false;

                sticky = false;
                prevSticky = false;
                stickyTransition = false;
                return;
            }

            if (hoverHeight > stickyHeight) {
                Debug.LogWarning("hoverHeight should not be larger than the stickyHeight of the controller.");
            }

            // Update sticky state
            StickyHitType type = StickyHit(out hit);
            sticky = type != StickyHitType.None;
            stickyTransition = prevSticky != sticky;
            prevSticky = sticky;

            // Update grounded state
            if (sticky) {
                if (hit.distance <= hoverHeight + 0.05f && Vector3.Dot(rb.velocity, hit.normal) <= 0) {
                    switch (type) {
                    case StickyHitType.Slip:
                        groundedState = GroundedState.Slip;
                        break;
                    case StickyHitType.Sticky:
                        if (groundedState != GroundedState.Grounded) {
                            groundedState = GroundedState.Grounded;
                        }
                        break;
                    }
                }
            } else {
                groundedState = GroundedState.Airborne;
            }

            // Update transition states
            bool grounded = groundedState == GroundedState.Grounded;
            groundedTransition = prevGrounded != grounded;
            prevGrounded = grounded;

            bool slip = groundedState == GroundedState.Slip;
            slipTransition = prevSlip != slip;
            prevSlip = slip;

            bool airborne = groundedState == GroundedState.Airborne;
            airborneTransition = prevAirborne != airborne;
            prevAirborne = airborne;

            // Update surface normal
            if (groundedState != GroundedState.Airborne) {
                surfaceNormal = hit.normal;
            } else {
                surfaceNormal = Vector2.up;
            }

            // Only stick to surface if player will remain sticky
            if (WillBeStickyHit(out _) != StickyHitType.None && sticky && groundedState != GroundedState.Airborne) {
                rb.velocity += new Vector3(0, hoverSpring.Solve(dt, hit.distance, rb.velocity.y, hoverHeight - 0.05f));
            }
        }

        private float dt;
        private void FixedUpdate() {
            dt = Time.fixedDeltaTime;

            HandleGrounded();

            // Calcuate bounding box size relative to ground
            float _height = height;
            if (groundedState == GroundedState.Grounded) {
                _height -= hit.distance;
            }
            collider.height = _height;
            collider.center = new Vector3(0, _height / 2f);
            collider.radius = radius;

            // Calculate bottom relative to ground
            bottom = transform.position;
            if (groundedState == GroundedState.Grounded) {
                bottom.y -= hit.distance;
            }

            // Gravity
            if (groundedState != GroundedState.Grounded) {
                rb.velocity += Vector3.down * gravity * dt;
            }
        }
    }
}
