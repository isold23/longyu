CKEDITOR.plugins.add( 'myAddImage',{  
    init : function( editor )  
    {     
       /* 
       /* 获取CKEditorFuncNum 
       */  
       var getFuncNum = function(url) {  
          var reParam = new RegExp('(?:[\?&]|&amp;)CKEditorFuncNum=([^&]+)', 'i') ;  
          var match = url.match(reParam) ;  
          return (match && match.length > 1) ? match[1] : '' ;  
        };  
       /* 
       /*  iframe onload处理  
        *  这段可以放在外面，根据不同的返回值自行进行处理 
        */  
        var getAjaxResult = function (t){  
            var _id = this.getId();  
            var _doc = this.getFrameDocument();  
            //获取页面返回值  
            var data = _doc.getBody().getHtml();  
            //firebrowser的处理  
            CKEDITOR.tools.callFunction(t.listenerData, data);  
            this.removeListener('load', getAjaxResult);  
        }  
  
        CKEDITOR.dialog.add( 'myAddImage', function( editor )  
        {  
            return {  
                    title : '插入代码',  
                    minWidth : 700,  
                    minHeight : 400,  
                    contents :   
                    [  
                        {  
                            id : 'addImage',  
                            label : '添加图片',  
                            title : '添加图片',  
                            filebrowser : 'uploadButton',  
                            elements :  
                            [  
                              {      
                                  id : 'txtUrl',  
                                  type : 'text',  
                                  label : '图片网址',  
                                  required: true  
                              },  
                              {  
                                    id : 'photo',  
                                    type : 'file',  
                                    label : '上传图片',  
                                    style: 'height:40px',  
                                    size : 38  
                              },  
                              {  
                                   type : 'fileButton',  
                                   id : 'uploadButton',  
                                   label : '上传',  
                                   filebrowser :  
                                   {  
                                        action : 'QuickUpload',  
                                        target : 'addImage:txtUrl',  
                                        onSelect:function(fileUrl, errorMessage){  
                                            //在这里可以添加其他的操作  
                                        }  
                                   },  
                                   onClick: function(){  
                                        var d = this.getDialog();  
                                        var _photo =  d.getContentElement('addImage','photo');  
                                        _funcNum = getFuncNum(_photo.action);  
                                        var _iframe =  CKEDITOR.document.getById(_photo._.frameId);  
                                        //可以查看ckeditor.event doc 了解此段代码  
                                        //http://docs.cksource.com/ckeditor_api/  
                                        _iframe.on('load', getAjaxResult, _iframe, _funcNum);  
                                   },  
                                   'for' : [ 'addImage', 'photo']  
                              }  
                            ]  
                        }  
                   ],  
                   onOk : function(){  
                       _src = this.getContentElement('addImage', 'txtUrl').getValue();  
                       if (_src.match(/(^\s*(\d+)((px)|\%)?\s*$)|^$/i)) {  
                           alert('请输入网址或者上传文件');  
                           return false;  
                       }  
                       this.imageElement = editor.document.createElement( 'img' );  
                       this.imageElement.setAttribute( 'alt', '' );  
                       this.imageElement.setAttribute( 'src', _src );  
                       //图片插入editor编辑器  
                       editor.insertElement( this.imageElement );  
                   }  
            };  
        });  
        editor.addCommand( 'myImageCmd', new CKEDITOR.dialogCommand( 'myAddImage' ) );  
        editor.ui.addButton( 'AddImage',  
        {  
                label : '图片',  
                icon: this.path + 'code.gif',  
                command : 'myImageCmd'  
        });  
    },  
    requires : [ 'dialog' ]  
});  