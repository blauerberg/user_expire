<?php
// $Id$


/**
 * @file
 * Administration page callback file for the user_expire module.
 */

function user_expire_admin_settings() {
  $form['user_expire_default_date'] = array(
    '#type' => 'textfield',
    '#size' => 16,
    '#description' => t('Default date to consider the user expired.') . ' ' .
      t('Format: PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.') .
      ' '. t('If blank, the user never expire.'),
    '#default_value' => variable_get('user_expire_default_date', ''),
  );

  return system_settings_form($form);
}

function user_expire_admin_settings_validate($form, $form_state) {
  $expire_date =  &$form_state['values']['user_expire_default_date'];
  if (!empty($expire_date) and !strtotime($expire_date)) {
    form_set_error('user_expire_default_date', 'This values should be in PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.');
  }
}

