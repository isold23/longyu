CKEDITOR.plugins.add( 'myCode',{
	init : function( editor )
	{
		CKEDITOR.dialog.add( 'myCode', function( editor )
		{
			return {
				title : '插入代码',
				minWidth : 400,
				minHeight : 300,
				contents: [{
					id: 'code_content',
					name: 'code_content',
					label: 'code_content',
					title: 'code_content',
					elements: [
					{
						type: 'textarea',
						label: '代码',
						id: 'code',
						rows: 20,
						'default': ''
					}]
				}],

				onOk: function()
				{
					code = this.getValueOf('code_content', 'code');
					html = '' + code + '';
					editor.insertHtml("<p class=\"code\" >" + html + "</p><br />");
				}
				
			};
		});
		editor.addCommand( 'myCodeCmd', new CKEDITOR.dialogCommand( 'myCode' ) );
		editor.ui.addButton( 'Code',
		{
			label : '插入代码',
			icon: this.path + 'code.gif',
			command : 'myCodeCmd'
		});
	},
	requires : [ 'dialog' ]
});