<?php
// $Id$

/**
 * @file
 * Page callback file for the user_expire module.
 */

function user_expire_user_settings($account) {
  return drupal_get_form('user_expire_edit_user', $account);
}

function user_expire_edit_user($form_state, $account = NULL) {
  if (empty($account)) {
    global $user;
    $account = $user;
  }

  $form = array();
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );

  $form['expire'] = array(
    '#type' => 'textfield',
    '#size' => 16,
    '#description' => t('The date to consider the user expired.') . ' ' .
      t('Format: dd-mm-YYYY.') . ' ' . t('If blank, user never expire.'),
    '#default_value' => _user_expire_get_expiration_date($account->uid),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function user_expire_edit_user_validate($form, &$form_state) {
  $date = $form_state['values']['expire'];

  if ($date != NULL && !preg_match("/\d{2}-\d{2}-\d{4}/", $date)) {
    form_set_error('expire', t('Invalid format.') . ' ' . t('Format must be dd-mm-YYYY.'));
  }

  if ($date != NULL && strtotime($date) < strtotime('now')) {
    form_set_error('expire', t('date cannot be earlier than today.'));
  }
}

function user_expire_edit_user_submit($form, &$form_state) {
  if (strcmp($form_state['values']['expire'], '') == 0) {
    _user_expire_delete_entry($form_state['values']['uid']);
  }
  else {
    _user_expire_update_entry($form_state['values']['uid'], strtotime($form_state['values']['expire']));
  }
  drupal_set_message('Expiration date has been updated');
}

