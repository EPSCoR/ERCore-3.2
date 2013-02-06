<?php
//THIS FILE IS DEPRECATED
//module_load_include('php', 'er', 'builder');
/*
 * This is an implementation of hook_block
 * This defines what blocks are available by this module.
 */
function er_block($op = 'list', $delta = 0, $edit = array()){
	//this defines the default values that will be set if nothing specific is set below
	$blocks_default = array(
		'subject'=>'', //The block's title
		'info'=>'A block defined by the er module.', //block description that shows up in the blocks admin page
		'title'=>'', //This is being used to define the title displayed above a graph
		'subtitle'=> '', //Defines the subtitle displayed below the main title on a graph
		'caption'=>'', //Caption that appears at the bottom of the block (right justified)
		'type'=>'' //Defines the type of output, the default is to just use dsm to display the data to admins 
	);
	//allows for easier customization of the labels relating to the block
	//you can add extra meta-data that will be passed down the chain of functions
	$blocks = array(
		'new_content_button_block'=>array(
			'info'=>t('New content button'),
			'title'=>'',
			'theme'=>'er_new_content_button'
		),
		'mike_block'=>array(
			'info'=>t('Login (with destination)'),
			'view'=>'_mike_block_proc'
		)
	);
	switch ($op) {
		case 'list':
			$list = array();
			foreach($blocks as $title=>$vals)
				$list[$title] = array('info'=>$vals['info']);
			return $list;
		case 'view':
			$info = $blocks[$delta];
			if ($info['view'])
				return $info['view']();
			else if ($info['theme'])
				return array(
					'subject'=>'',
					'content'=>theme($info['theme'])
				);
			else
				return array(
					'subject'=>'Error',
					'content'=>'This block is broken!'
				);
			//return er_blocks_data($delta, array_merge($blocks_default, $blocks[$delta]));
	}
}

function _mike_block_proc(){
	$wherearewe = ($_GET['q'] == 'frontpage') ? '' : $_GET['q'];
	$block_content = l('Login', 'login', array('query' => array('goto' => $wherearewe))); 
	$block['content'] = '<ul class="login-save-dest"><li>'. $block_content . '</li></ul>';
	$block['content'] = '<span class="login-save-dest">'. $block_content . '</span>';
	return $block;
}

/***********************************************************************************
 * Notice: This function does not hook anything
 * This function is being used to generate data that will be inserted into a block
 ***********************************************************************************/
function er_blocks_data($delta = 0, &$info){

}

/***************************************************************************
 * formats the output generated by er_blocks_data
 ***************************************************************************/
//function er_blocks_theme($data, $delta, &$info){
//	$output = "";
//	if ($data){
//		if ($delta == 'participants_block'){
//			$group = "";
//			//dsm($data);
//			foreach ($data as $dv=>$d){
//				if ($group != $d['inv']){
//					$output .= "</ul>";
//					$group = $d['inv'];
//					$output .= "<h3>$group</h3>";
//					$output .= "<ul>";
//				}
//				$output .= "<li>".l($d['realname'], 'user/'.$d['uid'])."</li>";
//			}
//			$output .= "</ul>";
//		}else if ($info['type'] == 'pie'){
//			drupal_add_js(drupal_get_path('module', 'er') .'/js/highcharts.js', 'file'); //primary highcharts js
//			drupal_add_js(drupal_get_path('module', 'er') .'/js/modules/exporting.js', 'file'); //exports highcharts
//			$series_data = array();
//			foreach($data as $v)
//				$series_data[] = array($v['name'], intVal($v['y']));//note: intVal is necessary for json encoding to be correct
//			$series = array(
//				array(
//					'type'=>'pie',
//					'name'=>$info['title'],//name of the series
//					'data'=>$series_data
//				)
//			);
//			$output = theme('er_chart_block', $series, $info);
//		}else if ($info['type'] == "grid"){
//				//REMOVE THESE TWO LINES FOR LIVE SITE:
//				foreach ($data as $k=>$d) $data[$k]['count'] = rand(1,15);
//				$output .= 'Im randomizing the counts to show off the color gradient...';
//			
//			$output .= '<div class="clearfix">';
//			//$colors = array(array(28,53,136), array(102,21,16));//color range: two RGB values
//			$colors = array(array(69,115,167), array(170,70,68));//color range: two RGB values
//			$max = 0;
//			
//			foreach ($data as $d)
//				if ($d['count'] > $max) $max = $d['count'];
//			
//			foreach ($data as $d){
//				$percent = ($d['count']-1)/($max-1);//this will make it so 1 will count as zero%
//				$color = '#';
//				foreach (range(0,2) as $c)
//					$color .= dechex($colors[0][$c]+($colors[1][$c]-$colors[0][$c])*$percent);
//				
//				$output .= '<div style="float:left;width:48%;margin-left:1px;margin-top:1px;border:1px solid black;min-height:3em;min-width:200px;">';
//					$output .= '<div style="float:right;padding:2px;font-weight:bold;color:'.$color.';">x'.$d['count'].'</div>';
//					$output .= '<div style="font-weight:normal;padding:2px;">'.$d['name'].'</div>';
//				$output .= '</div>';
//			}
//			$output .= '</div>';
//		}else if ($info['type'] == "table"){
//			//dsm($data);
//			$output = "<table>";
//			if ($info['table_labels']){
//				$output .= '<thead class="tableHeader-processed">';
//					$output .= '<tr class="region">';
//					foreach ($info['table_labels'] as $l)
//							$output .= "<th>{$l}</th>";
//					$output .= "</tr>";
//				$output .= "</thead>";
//			}
//			$even = true;
//			foreach ($data as $d){
//				$output .= '<tr class="'.($even?'even':'odd').'">';
//				if ($info['table_labels']){
//					foreach ($info['table_labels'] as $lk=>$l)
//						$output .= "<td>{$d[$lk]}</td>";
//				}else{
//					foreach ($d as $lk=>$l)
//						$output .= "<td>$l</td>";
//				}
//				$output .= "</tr>";
//				$even = !$even;
//			}
//			$output .= "</table>";
//		}else{
//			d($delta);
//			d($info);
//			d($data);
//		}
//	}
//	return array(
//		'subject'=>$info['subject'],
//		'content'=>$output
//	);
//}