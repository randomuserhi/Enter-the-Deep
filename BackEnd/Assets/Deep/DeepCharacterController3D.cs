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
    }
}
