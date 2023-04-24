#include <Novice.h>
#include <Matrix4x4.h>
#include <Vector3.h>
#include <cassert>

const char kWindowTitle[] = "LE2A_08_スヤマハナ";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char a[]) {
	Novice::ScreenPrintf(x, y, "%s", a);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, 20 + y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector3, const char a[]) {
	Novice::ScreenPrintf(x * kColumnWidth, 20 + y, "%6.02f", vector3.x);
	Novice::ScreenPrintf(x * kColumnWidth + 60, 20 + y, "%6.02f", vector3.y);
	Novice::ScreenPrintf(x * kColumnWidth + 120, 20 + y, "%6.02f", vector3.z);
	Novice::ScreenPrintf(x * kColumnWidth + 200, 20 + y, "%s", a);
}

//1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 Return{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				Return.m[i][j] = 1;
			}
		}
	}
	Return.m[3][0] = translate.x;
	Return.m[3][1] = translate.y;
	Return.m[3][2] = translate.z;
	return Return;
}

//2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 Return{};
	Return.m[0][0] = scale.x;
	Return.m[1][1] = scale.y;
	Return.m[2][2] = scale.z;
	Return.m[3][3] = 1;
	return Return;
}

//3.座標返還
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 Return{};
	Return.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	Return.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	Return.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	Return.x /= w;
	Return.y /= w;
	Return.z /= w;
	return Return;
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 translate{ 4.1f, 2.6f, 0.8f };
	Vector3 scale{ 1.5f, 5.2f, 7.3f };
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Vector3 point{ 2.3f, 3.8f, 1.4f };
	Matrix4x4 transformMatrix = {
		1.0f, 2.0f, 3.0f, 4.0f,
		3.0f, 1.0f, 1.0f, 2.0f,
		1.0f, 4.0f, 2.0f, 3.0f,
		2.0f, 2.0f, 1.0f, 3.0f
	};
	Vector3 transformed = Transform(point, transformMatrix);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		VectorScreenPrintf(0, 0, transformed, "transformed");
		MatrixScreenPrintf(0, 40, translateMatrix, "translateMatrix");
		MatrixScreenPrintf(0, 40 + kRowHeight * 5, scaleMatrix, "scaleMatrix");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
