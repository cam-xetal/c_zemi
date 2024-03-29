// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		ピクセルスシェーダー関連定義部
// 
// 				Ver 3.08a
// 
// -------------------------------------------------------------------------------

#define DX_PS_CONSTF_ZERO_HALF_ONE_TWO          0		// x=0.0f, y=0.5f, z=1.0f, w=2.0f
#define DX_PS_CONSTF_AMBIENT_EMISSIVE           1		// マテリアルエミッシブカラー + マテリアルアンビエントカラー * グローバルアンビエントカラー
#define DX_PS_CONSTF_MATERIAL_START             2		// マテリアル情報の格納開始アドレス
#define DX_PS_CONSTF_MATERIAL_SIZE              3		// マテリアル用のレジスタの数
#define DX_PS_CONSTF_MAT_DIFFUSE                0		// マテリアルのディフューズカラー
#define DX_PS_CONSTF_MAT_SPECULAR               1		// マテリアルのスペキュラカラー
#define DX_PS_CONSTF_MAT_POWER                  2		// マテリアルのスペキュラハイライトのパワー
#define DX_PS_CONSTF_FACTORCOLOR                5		// 透明度等
#define DX_PS_CONSTF_TOON_OUTLINE_COLOR         6		// トゥーンレンダリングの輪郭線の色
#define DX_PS_CONSTF_TOON_OUTLINE_WIDTH         7		// トゥーンレンダリングの輪郭線の太さ
#define DX_PS_CONSTF_LIGHT_START                9		// ライト情報の格納開始アドレス
#define DX_PS_CONSTF_LIGHT_UNITSIZE             3		// ライトの情報一つ辺りの使用レジスタの数
#define DX_PS_CONSTF_LGT_DIFFUSE                0		// ライトのディフューズカラー
#define DX_PS_CONSTF_LGT_SPECULAR               1		// ライトのスペキュラカラー
#define DX_PS_CONSTF_LGT_AMBIENT                2		// ライトのアンビエントカラーとマテリアルのアンビエントカラーを乗算したもの
#define DX_PS_CONSTF_LIGHT2_START               32		// ライト拡張情報の格納開始アドレス
#define DX_PS_CONSTF_LIGHT2_UNITSIZE            7		// ライト拡張情報一つ辺りに使用するレジスタの数
#define DX_PS_CONSTF_LGT2_POSITION              0		// ライトの位置( ビュー空間 )
#define DX_PS_CONSTF_LGT2_DIRECTION             1		// ライトの方向( ビュー空間 )
#define DX_PS_CONSTF_LGT2_DIFFUSE               2		// ライトのディフーズ色
#define DX_PS_CONSTF_LGT2_SPECULAR              3		// ライトのスペキュラ色
#define DX_PS_CONSTF_LGT2_AMBIENT               4		// ライトのアンビエント色とマテリアルのアンビエントカラーを乗算したもの
#define DX_PS_CONSTF_LGT2_RANGE_FALLOFF_AT0_AT1 5		// ライトの x:有効距離の二乗 y:フォールオフ z:距離減衰パラメータ０ w:距離減衰パラメータ１
#define DX_PS_CONSTF_LGT2_AT2_SPOTP0_SPOTP1     6		// ライトの x:距離減衰パラメータ２ y:スポットライト用パラメータ０( cos( Phi / 2.0f ) ) z:スポットライト用パラメータ１( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )

