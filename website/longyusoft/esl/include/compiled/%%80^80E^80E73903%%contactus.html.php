<?php /* Smarty version 2.6.22, created on 2011-10-15 12:02:59
         compiled from contactus.html */ ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "header.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
<div id = "subpage">
<div id="subpage-item">
<div id = "subcontent_no_background">

	<div id="contactus-info">
		

	<h1><?php echo $this->_tpl_vars['web_name']; ?>
</h1>


		<div class="unit-body">
</br>
		<div id = "contactus-info-item">
		<?php echo $this->_tpl_vars['address_key']; ?>
:  <?php echo $this->_tpl_vars['address']; ?>

		</div>
	</br>
		<div id = "contactus-info-item">
		<?php echo $this->_tpl_vars['email_key']; ?>
: <a href="mailto:<?php echo $this->_tpl_vars['email']; ?>
"><?php echo $this->_tpl_vars['email']; ?>
</a> 
		</div>
	</br>
		<div id = "contactus-info-item">
	<?php echo $this->_tpl_vars['telephone']; ?>
: (+86) 13911405813(<?php echo $this->_tpl_vars['china']; ?>
)  </br>
	&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp(+86) 10 60752398 (<?php echo $this->_tpl_vars['china']; ?>
)   </br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp(+254) 20 3513306 (<?php echo $this->_tpl_vars['kenya']; ?>
)
		</div>
	</br>
		<div id = "contactus-info-item">
		<?php echo $this->_tpl_vars['fax']; ?>
:  (+254) 20 3513305
		</div>
	</br>
	</div>

	</div><!-- contactus-info -->
	
	

</div><!-- subcontent -->

<div id = "sidebar">
	<div id = "sidebar-item">


	</div><!-- sidebar item end -->
</div><!-- sidebar end -->

</div><!-- subpage item end -->
</div><!-- subpage end -->
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "footer.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>

