#target photoshop
app.bringToFront();

if(documents.length == 0){
    alert("没有可处理的图层");
}
else {
    var visibility = false;
    var docRef = activeDocument;
    changeLayerName (docRef) ;
}

function changeLayerName (layer) {
    var layers = layer.layers;
    if (layers ) {
        for(var i = 0;i < layers.length;i++){
            layers [i]. name = [ i]+"";  ////名称就是层下标
            changeLayerName (layers [i]) ;
        }
    }
}
