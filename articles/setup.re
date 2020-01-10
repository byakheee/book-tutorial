={setup} Re:VIEWでの執筆環境を整える

#@# NOTE author:vvakame

まずはRe:VIEWで執筆するための環境を整えましょう。

TechBoosterでは、GitHubが提供するエディタであるAtom@<fn>{atom}と追加パッケージであるlanguage-review@<fn>{language-review}を使って執筆しています。
そしてGitHubなどにpushする前に、Ruby版のRe:VIEW@<fn>{review}を使ってHTMLやPDFの生成チェックを行う運用になっています。

生成チェックは、language-reviewがreview.js@<fn>{review.js}というJavaScriptによるRe:VIEWの移植版を使っているために必要な作業です。
review.jsは現在のところ、PDFを生成することなどができませんし、文章の解釈もRuby版と厳密には一致しません。

本書執筆時点での各ツールのバージョンは次のとおりです。

#@# TODO 入稿前にここのバージョンを再確認すること

 * Atom v1.18.0
 * language-review 0.15.3
 * Re:VIEW 2.3.0

//footnote[atom][@<href>{https://atom.io/}]
//footnote[language-review][@<href>{https://atom.io/packages/language-review}]
//footnote[review][@<href>{https://github.com/kmuto/review}]
//footnote[review.js][@<href>{https://github.com/vvakame/review.js}]

== Atomとlanguage-reviewのセットアップ

#@# NOTE author:vvakame

Atomエディタをインストールします。完了後、Atomを立ち上げ、設定からlanguage-reviewをインストールします（@<img>{install-language-review}）。

#@# Mac OS XであればAtomを起動した後、メニューのAtom > Install Shell Commandsを選ぶと@<code>{/usr/local/bin/}に@<code>{apm}コマンドがインストールされるので、ターミナルから@<code>{apm install language-review}を実行でもOKです。
#@# vv: https://github.com/atom/atom/issues/7570 この辺のIssueにワイの新MBP引っかかってるんだけど他の人の環境だとどうなのかわからない…

//image[install-language-review][language-reviewをインストールする]{
//}

次に適当な名前の@<tt>{.re}ファイル（例: test.re）を作ります。

作成後、このファイルをAtomで開きます。
デフォルトの編集モードはRe:VIEW以外になっているため、クリックして@<fn>{atom-tips}Re:VIEWに切り替えます（@<img>{language-review-grammar1}、@<img>{language-review-grammar2}@<fn>{atom-images-disclaimer}）。
#@# vv TODO この辺新規の環境でどうなるか再確認したさがある…（新PCでこの操作必要だった記憶がないけど無意識にやってるかもしれないしわからん）

//image[language-review-grammar1][モード切り替え前]{
//}
//image[language-review-grammar2][このように切り替えるのだ]{
//}

パッケージのインストール時に、依存する別パッケージ（linter）のインストールも行っています。
動作がおかしい気がする場合、Atomを完全に終了させてから起動しなおしてみてください。

#@# また、人柱用ですがMac OS X環境ではAtomのインストールからlanguage-reviewの導入までを行うインストールスクリプトを用意してあります。

#@# //cmd{
#@# curl -L https://github.com/vvakame/language-review/raw/master/install.sh | bash
#@# //}

language-reviewは、Atomを通じてさまざまな便利な機能を提供します。
よく使うのは次のとおりです。

 * シンタックスハイライト
 * 文法ミスの警告
 * 文章の校正支援
 * HTMLプレビュー
 * Re:VIEWの記法一覧
 * アウトライン表示とジャンプ

@<img>{language-review-sample}がサンプルです。

//image[language-review-sample][language-reviewの画面サンプル]{
//}

//footnote[atom-tips][Mac OS Xの場合、Command+Shift+Pでコマンドパレットが開くのでgrammarなどそれっぽいワードを投げ込むとマウスなしで操作できます]
//footnote[atom-images-disclaimer][プラグインの導入状態やAtomのバージョンによって、画像どおりの見た目じゃない場合のほうが多いはずです]

=={install_review} Re:VIEWをインストールする

#@# NOTE author:vvakame

次に、Ruby版Re:VIEWをインストールします。
これはPDFやEPUBの生成などの最終出力を行うのに必要です。

RubyとRubyGemsは、すでに利用可能な環境になっているものとして解説します。
インストールは単に次のコマンド@<fn>{experimental-review}を実行するだけです（Rubyのインストール方法次第ではsudoが必要となる場合もあります）。

//cmd{
$ gem install review
//}

これだけです。
詳しい使い方は@<chapref>{review-introduction}で解説します。

とりあえず試してみたい場合、次のコマンドを実行してください。

//cmd{
$ review-init sample
$ cd sample

# もしrakeコマンドがまだ入っていなかったら（sudoが必要な場合もある）
$ gem install rake

# 各種ビルド HTML & PDF & EPUB
$ rake html_all
$ rake clean pdf
$ rake clean epub
//}

このコマンドではHTML、PDF、EPUB形式でサンプルをそれぞれ出力しています。

//footnote[experimental-review][review-pegという実験的パッケージがありますが熱心なRe:VIEW信者でない限り通常のreviewを使えばよいでしょう]

===[column] Ruby導入の手引き Mac OS X、Linux編

Macの場合、何もしなくてもデフォルトでRubyが導入されています。
この状態だとgem installを実行するときにsudoが必要になります。
またデフォルトのRubyのバージョンは若干古いため、最新のものを入れたほうがよいでしょう。

システムのデフォルトのままだと、破壊的（かもしれない）操作をするのが怖いですし、イザというときにリセットすることもやりにくいです。

万一のときに@<code>{rm -rf ~/.rbenv}すればよい環境を作っておくと、精神的安らぎが得られます。

そのため本書ではrbenvの利用を推奨しています。
rbenvのインストール自体は公式サイト@<fn>{rbenv}に譲ります。

rbenvインストール後の手順は次のとおりです。

//cmd{
$ rbenv install --list
# 最新のを適当に入れれば良い 執筆時点では 2.4.1
$ rbenv install 2.4.1
# グローバルなrubyコマンドのバージョンを設定する localも存在する
$ rbenv global 2.4.1
# reviewをインストール
$ gem install review
//}

===[/column]

//footnote[rbenv][@<href>{https://github.com/sstephenson/rbenv#installation}]

===[column] Ruby導入の手引き Windows編

RubyInstaller@<fn>{rubyinstaller}を使うとよいでしょう。
しかし、TechBoosterでは、Windows環境下ではロクなLaTeX環境を構築できていないのでPDFの出力に難があり、素直に仮想環境を利用しています。
PDFを生成する必要がなければ、試す価値があるでしょう。

===[/column]

//footnote[rubyinstaller][@<href>{http://rubyinstaller.org/}]

== PDF出力を準備する

#@# NOTE author:vvakame

PDF出力の準備をします。
Re:VIEW文書をPDFに変換するにはLaTeX（platexまたはlualatexなど）を使います。
出力時の処理はreview形式→reviewツール実行→latex形式→platex実行→PDF という流れです。

==== Mac OS Xの場合

MacTeX@<fn>{mactex}を使いましょう。執筆時点ではMacTeX 2017が最新バージョンです。

//footnote[mactex][@<href>{https://www.tug.org/mactex/}]

==== Linuxの場合

texliveパッケージを利用します。
Ubuntu、Debianともに次のコマンドで導入できます。

//emlist{
$ sudo apt-get install texlive-lang-cjk texlive-fonts-recommended
//}

==== Windowsの場合

LaTeX環境の構築の難易度が高いため、Dockerなどの仮想環境を使うとよいでしょう。

==[column] Dockerとは？

Dockerは、最近はやりの仮想環境用のツールです。
Linuxカーネルに組み込みの機能を使って、軽量かつ無駄の少ない仮想化環境を実現しています。

Dockerはざっくり次の３つの利用方法があります。

 1. Dockerfile（イメージの設計図で主にコマンドの羅列）を書く
 2. Docker Hub@<fn>{docker-hub}などでホストされている他人が提供したDockerイメージを使う
 3. 他人の書いたDockerfileを元に自分のDockerfileを書く

本書ではDockerのインストール方法や使い方は解説しません。
その時々で適切なやり方を調べてみてください。Ruby入れたりTeX入れたりめんどくさすぎる！
という人のために、Dockerのイメージを用意@<fn>{docker-review}してあります。

//cmd{
$ docker run -i -t vvakame/review -v $(pwd):/book /bin/bash
//}

コマンドを実行すると、reviewとlatexの実行環境が整った環境が直ちに使えます。
コマンド実行後のディレクトリは@<code>{/book}ディレクトリにマウントされます。
適宜コンパイル用のコマンドを実行してください。

#@# prh:disable
実用的な例を知りたい場合は、この本のリポジトリのbuild-in-docker.shを参照してください。

#@# prh:disable
 *  @<href>{https://github.com/TechBooster/C89-FirstStepReVIEW-v2/blob/master/build-in-docker.sh}


//footnote[docker-hub][@<href>{https://hub.docker.com/}]
//footnote[docker-review][@<href>{https://hub.docker.com/r/vvakame/review/}]

==[/column]
