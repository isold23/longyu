<?php /* Smarty version 2.6.22, created on 2011-09-10 16:56:25
         compiled from comments.html */ ?>


<div id="comments"> 
			<ol id="comment_list"> 
<?php $_from = $this->_tpl_vars['comments_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['key'] => $this->_tpl_vars['comment']):
?>
<li id="box-<?php echo $this->_tpl_vars['comment']['id']; ?>
" <?php if ($this->_tpl_vars['comment']['odd'] == 1): ?>class='odd'<?php endif; ?> >
<div class="comment_data">
<a name="<?php echo $this->_tpl_vars['comment']['id']; ?>
">第<?php echo $this->_tpl_vars['key']; ?>
楼</a>  <?php echo $this->_tpl_vars['comment']['user_name']; ?>
<?php if ($this->_tpl_vars['comment']['user_id'] == -1): ?>(未注册用户)<?php endif; ?>  发表于    <?php echo $this->_tpl_vars['comment']['post_time']; ?>

</div>
<?php echo $this->_tpl_vars['comment']['content']; ?>

<div class="comment_reply"> 
                       <a href="javascript:replay(<?php echo $this->_tpl_vars['comment']['id']; ?>
);" rel="nofollow" id="replay-<?php echo $this->_tpl_vars['comment']['id']; ?>
">回复</a>                    </div> 
</li>
<?php endforeach; endif; unset($_from); ?>

      </ol> </div> 