using UnityEngine;

[RequireComponent(typeof(Deep.DeepCharacterController3D))]
public class TestMovement : MonoBehaviour {
    private Deep.DeepCharacterController3D controller;

    private void Start() {
        controller = GetComponent<Deep.DeepCharacterController3D>();
    }

    private void FixedUpdate() {
        Vector3 dir = -1 * Vector3.right * Time.fixedDeltaTime;
        controller.velocity += Vector3.ProjectOnPlane(dir, controller.SurfaceNormal).normalized * dir.magnitude * 80f;
        controller.velocity *= 0.8f;

        Debug.DrawRay(transform.position, Vector3.ProjectOnPlane(dir, controller.SurfaceNormal).normalized);
    }
}
