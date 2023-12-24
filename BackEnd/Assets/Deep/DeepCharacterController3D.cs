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
            get => grounded;
        }
        public bool GroundedTransition {
            get => groundedTransition;
        }
        public bool Airborne {
            get => airborne;
            set {
                airborne = value;
                grounded = !value;
                if (value) {
                    airborneTimer = 0;
                }
            }
        }

        // Settings
        public Vector3 size = new Vector3(1f, 2f, 1f);
        public Vector3 gravity = Vector3.down * 10f;

        private LayerMask surfaceLayerMask = Physics.AllLayers;

        private float hoverHeight = 0.25f;
        private float stickyHeight = 1f;
        private float maxSlopeCosAngle = 0.5f;

        // TODO(randomuserhi): Refactor hover spring -> notably SecondOrderDynamics class
        private SecondOrderDynamics hoverSpring = new SecondOrderDynamics(5f, 0.5f, 0f, 0f);

        // State
        private bool grounded = false;
        private bool prevGrounded = false;
        private bool groundedTransition = false;

        private bool sticky = false;
        private bool prevSticky = false;
        private bool stickyTransition = false;

        private bool airborne = true;
        private float airborneTimer = 0f;

        private Vector3 bottom = Vector3.zero;
        public Vector3 Bottom { get => bottom; }
        public Vector3 Center { get => bottom - gravity.normalized * size.y; }

        private void Start() {
            rb = GetComponent<Rigidbody>();
            collider = GetComponent<CapsuleCollider>();
        }

        /*private bool StickyHit(out RaycastHit2D hit, out bool willBeSticky) {
            // Will we be sticky in the future?
            Vector2 dir = Vector2.down;
            if (rb.velocity.x != 0 && rb.velocity.y < 0) {
                dir = rb.velocity.normalized;
            }
            RaycastHit2D willBeStickyHit = Physics2D.BoxCast(rb.position, new Vector2(size.x, 0.01f), 0, dir, Mathf.Infinity, surfaceLayerMask);
            willBeSticky = false;
            if (willBeStickyHit.collider != null) {
                willBeStickyHit.distance = Mathf.Abs(rb.position.y - willBeStickyHit.point.y);
                if (willBeStickyHit.distance < stickyHeight && Vector3.Dot(Vector2.down, willBeStickyHit.normal) < 0) {
                    if (Vector3.Dot(Vector2.up, willBeStickyHit.normal) >= maxSlopeCosAngle) {
                        willBeSticky = true;
                    }
                }
            }

            // Are we sticky now?
        }*/
    }
}
