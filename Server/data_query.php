<?php

//用于调试时监测数据库数据

$pdo=new PDO("mysql:host=localhost;dbname=ost","mwqdanmu","danmu666");

$sel_sql=("select * from danmu");
$res=$pdo->query($sel_sql);

while($row=$res->fetch())
{
print_r($row);
echo "<br></br>";
}

?>
