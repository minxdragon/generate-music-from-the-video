english translation from google translate: (please let me know if there are any errors!)

*Automatic music composition suitable for movies*

Automatic composition according to the color and motion of the animation

*Description*

By choosing a favorite movie and waiting for a while you can create MIDI that looks like a movie. It reflects the color and motion of the animation and the transition of the scene.

*something needed*

OpenCV, 
OpenMIDI and 
Qt are required:

pip install opencv
https://github.com/Agnostic/OpenMIDI
https://www.qt.io/download

*How to use*

If you compile and pass, you can do exe and if you push it you will see the UI. When you press Select Video, the window will appear, so select a movie. When you want to specify the output location / name, please put it in Name. If not, you can find out the sample.midi in the same location as Exe. Please wait for a while as auto generation starts as you start. It will end at 100%.

動画に合わせた自動楽曲制作
====

動画の色とか動きにあわせて自動作曲します

## せつめい
好きな動画を選択してしばらく待つだけで動画にあってるっぽいMIDIが出来ます。
動画の色や動き、場面の移り変わりとかを反映します。

## ひつようなもの
OpenCVとOpenMIDIとQtが必要です。

## つかいかた
コンパイルして通ればexeができて、それ押せばUIがでます。
Select Videoを押すと窓がでるので動画を選んでください。
出力場所・名前を指定したい時はNameにいれてください。
いれなかった場合はExeと同じ場所sample.midiって名前ででてきます。
Startをおすと自動生成がはじまるのでしばらくまっててください。
１００％になったらおわりです。
