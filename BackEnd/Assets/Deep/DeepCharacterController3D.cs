using UnityEngine;

namespace Deep {
    [RequireComponent(typeof(Rigidbody))]
    public class DeepCharacterController3D : MonoBehaviour {
        private Rigidbody rb;

        private void Start() {
            rb = GetComponent<Rigidbody>();
        }

        private bool grounded = false;
        public bool Grounded {
            get => grounded;
        }

        private bool sticky = false;

        private void FixedUpdate() {

        }
    }
}
