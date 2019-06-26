#!/usr/bin/php
<?php

$GRN = "\x1B[32m";
$RED = "\x1B[31m";
$YEL = "\x1B[33m";
$RST = "\x1B[0m";

$tests = array_diff(scandir('tests'), array('..', '.'));

function	test_md5_file($opt)
{
	global $tests;
	global $GRN;
	global $RED;
	global $RST;
	echo "MD5 File tests with options: '$opt'\n";
	foreach ($tests as $k => $file)
	{
		$test_cmd = "./ft_ssl md5 $opt tests/$file";
		$mine = shell_exec("./ft_ssl md5 $opt tests/$file");
		$bnch = shell_exec("md5 $opt tests/$file");
		if ($mine == $bnch)
		{
			$result = "  [".$GRN."PASS".$RST."] ";
			echo "$result  $test_cmd\n";
		}
		else
		{
			$result = "  [".$RED."FAIL".$RST."] ";
			echo "$result mine : \"".trim($mine)."\"\n";
			echo "          bench: \"".trim($bnch)."\"\n";
		}
	}
}

function 	test_md5_string($opt)
{
	global $tests;
	global $GRN;
	global $RED;
	global $RST;

	echo "MD5 String tests with options: '$opt'\n";
	foreach ($tests as $k => $file)
	{
		$test_cmd = "./ft_ssl md5 $opt -s [contents of $file]";
		$str = file_get_contents("tests/$file");
		$mine = shell_exec("./ft_ssl md5 $opt -s \"$str\"");
		$bnch = shell_exec("md5 $opt -s \"$str\"");
		if ($mine == $bnch)
		{
			$result = "  [".$GRN."PASS".$RST."] ";
			echo "$result   $test_cmd\n";
		}
		else
		{
			$result = "  [".$RED."FAIL".$RST."] ";
			echo "        mine : \"$mine\"\n";
			echo "        bench: \"$bnch\"\n";
			echo "$result   $test_cmd\n";
		}
	}
}

function	test_md5_stdin($opt)
{
	global $tests;
	global $GRN;
	global $RED;
	global $RST;

	echo "MD5 stdin tests with options: '$opt'\n";
	foreach ($tests as $k => $file)
	{
		$test_cmd = "cat tests/$file | ./ft_ssl md5 $opt";
		$mine = shell_exec("cat tests/$file | ./ft_ssl md5 $opt");
		$bnch = shell_exec("cat tests/$file | md5 $opt");
		if ($mine == $bnch)
		{
			$result = "  [".$GRN."PASS".$RST."] ";
			echo "$result   $test_cmd\n";
		}
		else
		{
			$result = "  [".$RED."FAIL".$RST."] ";
			echo "        mine : \"$mine\"\n";
			echo "        bench: \"$bnch\"\n";
			echo "$result   $test_cmd\n";
		}

	}
}

echo "SHA-256 Basic Tests:\n";

echo "File tests:\n";
foreach ($tests as $k => $file)
{
	$mine = shell_exec("./ft_ssl sha256 tests/$file");
	$bnch = shell_exec("openssl sha256 tests/$file");
	if ($mine == $bnch)
	{
		$result = "  [".$GRN."PASS".$RST."] ";
		echo "$result      : \"".trim($mine)."\"\n";
	}
	else
	{
		$result = "  [".$RED."FAIL".$RST."] ";
		echo "$result mine : \"".trim($mine)."\"\n";
		echo "          bench: \"".trim($bnch)."\"\n";
	}
}

echo "String tests:\n";
foreach ($tests as $k => $file)
{
	$str = file_get_contents("tests/$file");
	$mine = shell_exec("./ft_ssl sha256 -q -s \"$str\"");
	$bnch = shell_exec("cat tests/$file | openssl sha256");
	if ($mine == $bnch)
	{
		$result = "  [".$GRN."PASS".$RST."] ";
		echo "$result -s [$file]\n";
	}
	else
	{
		$result = "  [".$RED."FAIL".$RST."] ";
		echo "$result -s [$file]\n";
		echo "     mine : \"$mine\"\n";
		echo "     bench: \"$bnch\"\n";
	}
}

echo "Stdin tests:\n";
foreach ($tests as $k => $file)
{
	$mine = shell_exec("cat tests/$file | ./ft_ssl sha256");
	$bnch = shell_exec("cat tests/$file | openssl sha256");
	if ($mine == $bnch)
		$result = "  [".$GRN."PASS".$RST."] ";
	else
		$result = "  [".$RED."FAIL".$RST."] ";
	echo "$result [cat $file]\n";
}

echo "\nMD5 Basic Tests\n";
test_md5_file("");
test_md5_string("");
test_md5_stdin("");

echo "\nMD5 Tests with Options\n";
test_md5_file("-q");
test_md5_string("-q");
test_md5_stdin("-q");
test_md5_file("-r");
test_md5_string("-r");
test_md5_stdin("-r");
test_md5_stdin("-p");

echo "\n\nSHA-224 Basic Tests:\n";

echo "File tests:\n";
foreach ($tests as $k => $file)
{
	$mine = shell_exec("./ft_ssl sha224 tests/$file");
	$bnch = shell_exec("openssl sha224 tests/$file");
	if ($mine == $bnch)
	{
		$result = "  [".$GRN."PASS".$RST."] ";
		echo "$result      : \"".trim($mine)."\"\n";
	}
	else
	{
		$result = "  [".$RED."FAIL".$RST."] ";
		echo "$result mine : \"".trim($mine)."\"\n";
		echo "          bench: \"".trim($bnch)."\"\n";
	}
}

echo "String tests:\n";
foreach ($tests as $k => $file)
{
	$str = file_get_contents("tests/$file");
	$mine = shell_exec("./ft_ssl sha224 -q -s \"$str\"");
	$bnch = shell_exec("cat tests/$file | openssl sha224");
	if ($mine == $bnch)
	{
		$result = "  [".$GRN."PASS".$RST."] ";
		echo "$result -s [$file]\n";
	}
	else
	{
		$result = "  [".$RED."FAIL".$RST."] ";
		echo "$result -s [$file]\n";
		echo "     mine : \"$mine\"\n";
		echo "     bench: \"$bnch\"\n";
	}
}

echo "Stdin tests:\n";
foreach ($tests as $k => $file)
{
	$mine = shell_exec("cat tests/$file | ./ft_ssl sha224");
	$bnch = shell_exec("cat tests/$file | openssl sha224");
	if ($mine == $bnch)
		$result = "  [".$GRN."PASS".$RST."] ";
	else
		$result = "  [".$RED."FAIL".$RST."] ";
	echo "$result [cat $file]\n";
}


?>
