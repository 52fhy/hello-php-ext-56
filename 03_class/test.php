<?php 
class my_class_2 extends my_class{
    public function abstract_method(){}
}
$obj = new my_class_2();
var_dump($obj);
var_dump(my_class::TYPE_1, my_class::TYPE_TRUE, my_class::TYPE_STRING);