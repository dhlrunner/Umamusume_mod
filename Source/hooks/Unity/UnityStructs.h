#pragma once
namespace Unity
{
	// Unity Structs
	// UnityEngine.Color
	struct Color_t
	{
	public:
		// System.Single UnityEngine.Color::r
		float r;
		// System.Single UnityEngine.Color::g
		float g;
		// System.Single UnityEngine.Color::b
		float b;
		// System.Single UnityEngine.Color::a
		float a;
	};

	// UnityEngine.Vector2
	struct Vector2_t
	{
	public:
		// System.Single UnityEngine.Vector2::x
		float x;
		// System.Single UnityEngine.Vector2::y
		float y;
	};

	struct Vector2_Int_t {
		int m_X;
		int m_Y;
	};


	// UnityEngine.Vector3
	struct Vector3_t
	{
	public:
		// System.Single UnityEngine.Vector3::x
		float x;
		// System.Single UnityEngine.Vector3::y
		float y;
		// System.Single UnityEngine.Vector3::z
		float z;
	};

	enum class FullScreenMode {
		ExclusiveFullScreen,
		FullScreenWindow,
		MaximizedWindow,
		Windowed
	};

	// UnityEngine.ScreenOrientation
	enum class ScreenOrientation {
		Unknown,
		Portrait,
		PortraitUpsideDown,
		LandscapeLeft,
		LandscapeRight,
		AutoRotation,
		Landscape = 3
	};
}