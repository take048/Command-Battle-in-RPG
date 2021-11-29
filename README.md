# Command-Battle-in-RPG

RPGでのコマンド式のバトルを遊べるコンソールアプリケーションです。

使用言語：C言語

# ゲームの始め方
本アプリケーションはC言語で書かれているので、MAC OSの場合、通常のやり方でコンパイルしていただき、生成された実行ファイルを実行させてください。

例：MacOSの場合
```
gcc RPGHead.h RPGMain.c RPGArith.c
./a.out
```

アプリケーションに使用するテキストファイル、ソースコードはUTF-8で書かれているのでMAC OSでの動作を推奨します。
もし、Windowsで使用する場合は、全テキストファイルをShift-Jis(ANSI)に変換していただき、コンパイルと実行は以下のようにお願いします。

例：Windowsの場合
```
gcc RPGHead.h RPGMain.c RPGArith.c -finput-charset=UTF-8 -fexec-charset=CP932
a.exe
```

# ゲームの進め方
アプリケーションを実行させると以下のように表示されます。

![ゲームの進め方](screenshot/procedure1.png)

0を選択すると自分の名前を決めて、一から遊べます。
![ゲームの進め方](screenshot/procedure2.png)

1を選択すると、セーブデータを読み込み、前回遊んだ続きから遊ぶことができます。

ゲームが始まると敵が出現し、敵、プレイヤーのHP、プレイヤーの選択肢が表示されます。

![ゲームの進め方](screenshot/procedure3.png)

![ゲームの進め方](screenshot/procedure4.png)

出現する敵はランダムで選択され、、プレイヤーのレベルが高くなると様々な敵が出現します。

選択肢は以下の４つです。
- たたかう
- まほう
- アイテム
- にげる

## たたかう
「たたかう」を選択すると、プレイヤーは敵に攻撃します。

![ゲームの進め方](screenshot/procedure5.png)

プレイヤーの行動後、敵が攻撃してきます。

![ゲームの進め方](screenshot/procedure6.png)

プレイヤーの攻撃で敵のHPが0になると、戦闘終了に移行します。

![ゲームの進め方](screenshot/procedure7.png)

## まほう

「まほう」を選択すると、魔法選択肢が表示されます。

![ゲームの進め方](screenshot/procedure8.png)

この時、魔法を覚えていない場合表示されません。

![ゲームの進め方](screenshot/procedure9.png)

覚えている魔法を選択すると、魔法で攻撃します。

![ゲームの進め方](screenshot/procedure10.png)

魔法攻撃後は「たたかう」と同じです。

プレイヤーの行動後、敵が攻撃してきます。

![ゲームの進め方](screenshot/procedure6.png)

プレイヤーの魔法攻撃で敵のHPが0になると、戦闘終了に移行します。

![ゲームの進め方](screenshot/procedure7.png)

## アイテム

「アイテム」を選択すると、アイテム選択肢が表示されます。

![ゲームの進め方](screenshot/procedure11.png)

所持しているアイテムを選択するとHPが回復します。

![ゲームの進め方](screenshot/procedure12.png)

所持数が0のアイテムは使用できません。

![ゲームの進め方](screenshot/procedure13.png)

アイテム使用後は「たたかう」と同じです。

プレイヤーの行動後、敵が攻撃してきます。

![ゲームの進め方](screenshot/procedure6.png)

## にげる
「にげる」を選択すると、確率で戦闘から逃げることができます。

![ゲームの進め方](screenshot/procedure14.png)

失敗することもあります。

![ゲームの進め方](screenshot/procedure15.png)

「逃げる」が失敗した場合、敵が攻撃してきます。

![ゲームの進め方](screenshot/procedure6.png)

# 戦闘終了後
戦闘終了後、経験値が獲得でき、経験値が貯まるとレベルが上がることもあります。

![ゲームの進め方](screenshot/procedure16.png)

また確率でアイテムを取得することもあります。

その後、次の戦闘を始めるか、ゲームを終了するか、ステータスの確認が行えます。

![ゲームの進め方](screenshot/procedure17.png)

ステータスの確認ではレベル、現在のHP、最大HP、現在のMP、最大MP、攻撃力、防御力、次のレベルまでの経験値量が表示されます。

次の戦闘を始めると敵の出現から戦闘が開始します。

![ゲームの進め方](screenshot/procedure18.png)
