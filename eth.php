<?php

error_reporting(E_ALL);
ini_set("display_errors", 1);

function post($url, $fields)
{   
    var_dump(json_encode($fields));
    $post_field_string = json_encode($fields);
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 10);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $post_field_string);
    curl_setopt($ch, CURLOPT_POST, true);
    curl_setopt($ch, CURLOPT_HTTPHEADER, array('Accept: application/json', 'Content-Type: application/json'));
    $http_status = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    $response = curl_exec($ch);
    if (curl_errno($ch)) {
       echo 'Error:' . curl_error($ch);
    }
    var_dump($response);
    curl_close ($ch);
    return $response;
}
 
$rtnval = post('http://localhost:1112', array('jsonrpc'=>'2.0', 'method'=>'eth_accounts', 'params'=>[], 'id'=>1));
?>
rtn :: <?=$rtnval?>
