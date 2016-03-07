# SVDTools

スペクトル解析ツール群（特異値分解など）

cygwin上でしか動作確認していない。

## Build

当プロジェクトは以下のパッケージに依存している。まだインストールしていない場合は、cygwinのsetup.exe（64bitかどうか確認すること）から、インストールする。

* gcc-core（C言語コンパイラ）
* gcc-g++（C++コンパイラ）
* libboost-devel（C++用ライブラリ）
* cmake（C/C++用ビルドツール）
* make（C/C++用ビルドツール）

依存するパッケージをインストールしたら、cygwinでbuildフォルダ以下に移動し、`cmake ..`でビルド準備、`make`でビルドする。

以下コマンド例

```
cd build
cmake ..; make
```


## Usage

バイナリがいくつか生成される。特異値分解は'svd.exe'で行う。


### 特異値分解

```
./svd.exe -i spectrum.csv
```

とすると、同じディレクトリに.csvファイルが４つ生成される。

* spectrum_MatU.csv　右特異行列（混成基底行列）
* spectrum_MatV.csv　左特異行列（結合係数行列）
* spectrum_MatS.csv　特異値行列（対角成分が特異値）
* spectrum_VecS.csv 特異値を羅列したもの


### その他

multiply.exeは行列の掛け算を行う。
nmf.exeやnmf2.exeはNon-negative Matrix Factorizationを行う。


## Todo

* csv入出力ライブラリが昔書いたやつでうんこなので直す（新しくかいたやつはWTFCSVという名前で公開しているけどバグ放置したままなので直して入れ替える）
* 主成分分析もpythonでやるよりこっちでやったほうが統一感があるのでかく
* 混成基底空間を探索するときにはExcelのソルバーの非線形GRGを使っているけど、数理計画問題（最適化問題）に使われるアルゴリズム（準ニュートン法など）を使うべきで、それも書いたらここに追加する。
* もはや特異値分解だけじゃないプロジェクトになりそうなので改名して作り直したほうが良いかも
