using UnityEngine;

namespace Deep.Math {
    // TODO(randomuserhi): Re-write => inconsistent behaviour between classes etc...
    public class SecondOrderDynamics {
        private float xp;
        private float k1, k2, k3;

        public SecondOrderDynamics(float f = 0, float z = 0, float r = 0, float x0 = 0) {
            init(f, z, r, x0);
        }

        public void init(float f, float z, float r, float x0 = 0) {
            k1 = z / (Mathf.PI * f);
            k2 = 1 / ((2 * Mathf.PI * f) * (2 * Mathf.PI * f));
            k3 = r * z / (2 * Mathf.PI * f);

            xp = x0;
        }

        public float Solve(float T, float y, float yd, float x, float? xd = null) {
            if (xd == null) {
                xd = (x - xp) / T;
                xp = x;
            }
            float k2_stable = Mathf.Max(k2, 1.1f * (T * T / 4 + T * k1 / 2));
            //y = y + T * yd;
            //yd = yd + T * (x + k3 * xd.Value - y - k1 * yd) / k2_stable;
            //return y;
            //return yd;
            return T * (x + k3 * xd.Value - y - k1 * yd) / k2_stable;
        }
    }

    public class SecondOrderDynamics2D {
        private Vector2 xp, yd;
        private float k1, k2, k3;

        public SecondOrderDynamics2D(float f = 0, float z = 0, float r = 0) {
            init(f, z, r, Vector2.zero);
        }

        public void init(float f, float z, float r, Vector2 x0) {
            k1 = z / (Mathf.PI * f);
            k2 = 1 / ((2 * Mathf.PI * f) * (2 * Mathf.PI * f));
            k3 = r * z / (2 * Mathf.PI * f);

            xp = x0;
            yd = Vector2.zero;
        }

        public Vector2 Solve(float T, Vector2 y, Vector2 x, Vector2? xd = null) {
            if (xd == null) {
                xd = (x - xp) / T;
                xp = x;
            }
            float k2_stable = Mathf.Max(k2, 1.1f * (T * T / 4 + T * k1 / 2));
            y = y + T * yd;
            yd = yd + T * (x + k3 * xd.Value - y - k1 * yd) / k2_stable;
            return y;
        }
    }
}
