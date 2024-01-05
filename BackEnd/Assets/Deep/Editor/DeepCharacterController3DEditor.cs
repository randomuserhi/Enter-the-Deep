#if UNITY_EDITOR

using UnityEditor;

namespace Deep.Editor {
    [CustomEditor(typeof(DeepCharacterController3D))]
    public class DeepCharacterController3DEditor : UnityEditor.Editor {
        /*private readonly List<SerializedProperty> _propertiesToDraw = new List<SerializedProperty>();

        private void OnEnable() {
            AddCustomProperty("height");
        }

        private SerializedProperty AddCustomProperty(string propertyName) {
            var property = serializedObject.FindProperty(propertyName);
            _propertiesToDraw.Add(property);
            return property;
        }

        public override void OnInspectorGUI() {
            serializedObject.Update();

            DrawCustomProperties();

            serializedObject.ApplyModifiedProperties();
        }

        private void DrawCustomProperties() {
            foreach (var property in _propertiesToDraw) {
                EditorGUILayout.Separator();
                EditorGUILayout.PropertyField(property);
            }
        }*/
    }
}

#endif