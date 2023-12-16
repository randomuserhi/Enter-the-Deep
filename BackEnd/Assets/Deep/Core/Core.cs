using System.Text;
using UnityEngine;
using UnityEngine.LowLevel;
using UnityEngine.PlayerLoop;
using UnityEngine.SceneManagement;

namespace Deep.Core3D {
    public class Core : MonoBehaviour {
        private static Core instance;

        [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.BeforeSceneLoad)]
        private static void RuntimeInitialize() {
            // TODO(randomuserhi): Check if player loop is maintained between scenes
            // -> this code may need to be moved to OnSceneLoad

            // Setup Player Loop => Move FixedUpdate.ScriptRunBehaviourFixedUpdate to after FixedUpdate.DirectorFixedUpdatePostPhysics
            // This is needed because I want what is seen visually to match the current physics step:
            // OLD:
            // -> Update velocities, colliders etc...
            // -> Simulate Step
            // -> Render -> Say you updated colliders, the colliders on this render may be incorrect post the simulate step
            // NEW:
            // -> Simulate Step
            // -> Update velocities, colliders etc...
            // -> Render -> colliders are now correct since they will not get mis-aligned due to a simulate step inbetween
            //
            // reference: https://medium.com/@thebeardphantom/unity-2018-and-playerloop-5c46a12a677

            PlayerLoopSystem playerLoop = PlayerLoop.GetDefaultPlayerLoop();
            PlayerLoopSystem fixedUpdate = FindSubSystem<FixedUpdate>(playerLoop);
            PlayerLoopSystem? scriptRunBehaviourFixedUpdate = null;
            int i = 0;
            for (; i < fixedUpdate.subSystemList.Length; ++i) {
                if (fixedUpdate.subSystemList[i].type == typeof(FixedUpdate.ScriptRunBehaviourFixedUpdate)) {
                    scriptRunBehaviourFixedUpdate = fixedUpdate.subSystemList[i];
                    break;
                }
            }
            if (scriptRunBehaviourFixedUpdate == null) {
                Debug.LogError("Unable to find 'FixedUpdate.ScriptRunBehaviourFixedUpdate' in player loop! Leaving player loop as default.");
            } else {
                bool found = false;
                for (; i < fixedUpdate.subSystemList.Length - 1; ++i) {
                    fixedUpdate.subSystemList[i] = fixedUpdate.subSystemList[i + 1];
                    if (fixedUpdate.subSystemList[i].type == typeof(FixedUpdate.DirectorFixedUpdatePostPhysics)) {
                        found = true;
                        ++i;
                        break;
                    }
                }
                if (!found) {
                    Debug.LogWarning("Unable to find 'FixedUpdate.DirectorFixedUpdatePostPhysics' in player loop, appending 'FixedUpdate.ScriptRunBehaviourFixedUpdate' to end.");
                }
                fixedUpdate.subSystemList[i] = scriptRunBehaviourFixedUpdate.Value;
                PlayerLoop.SetPlayerLoop(playerLoop);
                DebugPlayerLoop(playerLoop);
            }

            SceneManager.sceneLoaded += OnSceneLoad;
        }

        private static PlayerLoopSystem FindSubSystem<T>(PlayerLoopSystem def) {
            if (def.type == typeof(T)) {
                return def;
            }
            if (def.subSystemList != null) {
                foreach (var s in def.subSystemList) {
                    var system = FindSubSystem<T>(s);
                    if (system.type == typeof(T)) {
                        return system;
                    }
                }
            }
            return default;
        }

        private static void DebugPlayerLoop(PlayerLoopSystem playerLoop) {
            StringBuilder sb = new StringBuilder();
            _DebugPlayerLoop(playerLoop, sb, 0);
            Debug.Log(sb.ToString());
        }
        private static void _DebugPlayerLoop(PlayerLoopSystem playerLoop, StringBuilder sb, int depth) {
            if (depth == 0) {
                sb.AppendLine("ROOT NODE");
            } else if (playerLoop.type != null) {
                for (int i = 0; i < depth; i++) {
                    sb.Append("\t");
                }
                sb.AppendLine(playerLoop.type.Name);
            }
            if (playerLoop.subSystemList != null) {
                depth++;
                foreach (var s in playerLoop.subSystemList) {
                    _DebugPlayerLoop(s, sb, depth);
                }
                depth--;
            }
        }

        private static void OnSceneLoad(Scene scene, LoadSceneMode mode) {
            Core exists = FindAnyObjectByType<Core>();
            if (exists != null) return;

            GameObject go = new GameObject();
            go.name = "Core";
            go.AddComponent<Core>();
        }

        private void Start() {
            if (instance != null) {
                Debug.LogError("Cannot have more than one Deep.Core instance");
                return;
            }
            instance = this;
        }
    }
}
