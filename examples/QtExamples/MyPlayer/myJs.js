.pragma library

var gMList;  //音乐文件列表
var gMPlayer;   //播放器

var gTableView; //访问数据模型
var gCurrentRow = -1; //保存当前歌曲的行号

var urls = new Array();

//设置全局MusicList对象
function initMusicList(list){
    gMList = list;
}

//设置全局Player对象
function initPlayer(player)
{
    gMPlayer = player;
}


//设置播放列表的TableView对象
function initListView(listView){
    gTableView = listView;
}



//设置MusicList的文件夹路径
function getMusiList(fileUrl){
    //检查路径是否已经添加过
    var i;
    for( i in urls){
        if(urls[i] == fileUrl)
            return 0;
    }
    urls[++i] = fileUrl;

    gMList.setPath(urls[i].toString().slice(8));
    return gMList.musicCount;
}

//播放音乐
function playMusic(row)
{

    if(row < 0 || row >=  gTableView.mCount)
        return;

    gCurrentRow = row;
    gMList.currentRow = row;

    var path = gTableView.model.get(gMList.currentRow).mPath;

    gMPlayer.stop();
    gMPlayer.source = path;
    gMPlayer.play();

}

//将毫秒转换成00:00形式
function calTime(value){
    var s = Math.round(value / 1000);
    var m = Math.round(s / 60);
    s = s % 60;

    var mm = "0" + m;
    if(m > 9)
        mm = "%1".arg(m);

    var ss = "0" + s;
    if(s > 9)
        ss = "%1".arg(s);
    return mm + ":" + ss;
}
