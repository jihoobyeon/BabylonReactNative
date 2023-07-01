import React, { useEffect, useState } from 'react';
import { View } from 'react-native';
import { Camera, Color4, HemisphericLight, MeshBuilder, Scene, Vector3 } from '@babylonjs/core';
import { EngineView, useEngine } from '@babylonjs/react-native';

export default function App() {
  const engine = useEngine();
  const [camera, setCamera] = useState<Camera>();

	useEffect(() => {
		if (engine) {
			const scene = new Scene(engine);
			scene.createDefaultCamera(true);
			scene.clearColor = new Color4(0, 1, 1, 1);
			const light = new HemisphericLight('light', new Vector3(0, 1, 1), scene);
			const sphere = MeshBuilder.CreateBox('box', { height: 2, width: 2, depth: 2 }, scene);
			const camera = scene.activeCamera!;
			camera.position = new Vector3(-5, 0, 3);
			setCamera(camera);
		}
	}, [engine]);

  return (
      <View style={{ flex: 1 }}>
        <EngineView camera={ camera } />
      </View>
  );
}
