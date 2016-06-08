#!/bin/bash

MYSHELL="$PWD/42sh"
REFER="/bin/tcsh -f"

CAT=`which cat`
GREP=`which grep`
SED=`which sed`
RM=`which rm`
TR=`which tr`
HEAD=`which head`
TAIL=`which tail`
WC=`which wc`
CHMOD=`which chmod`
EXPR=`which expr`
MKDIR=`which mkdir`
CP=`which cp`

STDERR_DEBUG=1

disp_test()
{
  id=$1
  $CAT tests | $GREP -A1000 "\[$id\]" | $GREP -B1000 "^\[$id-END\]" | $GREP -v "^\[.*\]"
}

prepare_test()
{
  local testfn="/tmp/.test.$$"
  local runnerfn="/tmp/.run.$$"
  local refoutfn="/tmp/.output.refer.$$"
  local shoutfn="/tmp/.output.shell.$$"

  WRAPPER="$runnerfn"

  echo "#!/bin/bash" > $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$REFER" ; echo exit \$?' > "$refoutfn" 2>&1" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$MYSHELL" ; echo exit \$?' > "$shoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn

  echo "#!/bin/bash" > $testfn
  echo "$TESTS" | $TR "²" "\n" >> $testfn

  chmod 755 $testfn
  chmod 755 $runnerfn
}

load_test()
{
  id=$1
  debug=$2
  SETUP=`disp_test "$id" | $GREP "SETUP=" | $SED s/'SETUP='// | $SED s/'"'//g`
  CLEAN=`disp_test "$id" | $GREP "CLEAN=" | $SED s/'CLEAN='// | $SED s/'"'//g`
  NAME=`disp_test "$id" | $GREP "NAME=" | $SED s/'NAME='// | $SED s/'"'//g`
  TESTS=`disp_test "$id" | $GREP -v "SETUP=" | $GREP -v "CLEAN=" | $GREP -v "NAME=" | $GREP -v "TESTS=" | $TR "\n" "²" | $SED s/"²$"//`

  prepare_test

  if [ $jenkins -eq 1 ]
  then
    $WRAPPER
  else
    $WRAPPER
  fi

  nb=`$CAT /tmp/.output.refer.$$ | $GREP -v '^\[1\]' | $WC -l`
  i=1
  ok=1
  while [ $i -le $nb ]
  do
    l=`$CAT /tmp/.output.refer.$$ | $GREP -v '^\[1\]' | $HEAD -$i | $TAIL -1`
    a=`$CAT /tmp/.output.shell.$$ | $GREP -v '^\[1\]' | $GREP -- "$l$" | $WC -l`
    if [ $a -eq 0 ]
    then
      ok=0
    fi
    i=`$EXPR $i + 1`
  done

  if [ $ok -eq 1 ]
  then
    if [ $debug -ge 1 ]
    then
      echo "Test $id ($NAME) : OK"
      if [ $debug -eq 2 ]
      then
        echo "Output $MYSHELL :"
        $CAT -e /tmp/.output.shell.$$
        echo "" 
        echo "Output $REFER :"
        $CAT -e /tmp/.output.refer.$$
        echo ""
      fi
    else
      echo "OK"
    fi
  else
    if [ $debug -ge 1 ]
    then
      echo "Test $id ($NAME) : KO - Check output in /tmp/test.$$/$id/" 
      $MKDIR -p /tmp/test.$$/$id 2>/dev/null
      $CP /tmp/.output.refer.$$ /tmp/test.$$/$id/tcsh.out
      $CP /tmp/.output.shell.$$ /tmp/test.$$/$id/mysh.out
    else
      if [ $STDERR_DEBUG -eq 1 ]
      then
        echo "Test $id ($NAME) : KO" >&2
        echo "---------- TCSH Output : ----------" >&2
        $CAT "/tmp/.output.refer.$$" >&2
        echo "---------- END ----------" >&2
        echo "---------- 42SH Output : ----------" >&2
        $CAT /tmp/.output.shell.$$ >&2
        echo "---------- END ----------" >&2
        echo "" >&2
        echo "KO"
      else
        echo "KO"
      fi
    fi
  fi
}

make_manifest()
{
  echo '{'
  echo '  "module": "B-PSU-156",'
  echo '  "project": "42sh",'
  echo '  "skills": {'
  i=0
  for lst in `cat tests | grep "^\[.*\]$" | grep -vi end | sed s/'\['// | sed s/'\]'//`
  do
  if [ $i -eq 1 ]
  then
    echo ','
  else
    i=1
  fi
  NAME=`disp_test "$lst" | $GREP "NAME=" | $SED s/'NAME='// | $SED s/'"'//g`
  echo '    "Test '$lst'": {'
  echo '      "output": ['
  echo '        {'
  echo '          "name": "'$NAME'",'
  echo '          "cmd": "./moul.sh -j '$lst'",'
  echo '          "expected": "^OK"'
  echo '        }'
  echo '      ]'
  echo -n '    }'
  done
  echo ""
  echo '  }'
  echo '}'
}

for sig in `trap -l`
do
  echo "$sig" | grep "^SIG" >/dev/null 2>&1
  if [ $? -eq 0 ]
  then
    trap "echo Received signal $sig !" $sig
  fi
done

if [ ! -f tests ]
then
  echo "No tests file. Please read README.ME" >&2
  exit 1
fi

if [ ! -f $MYSHELL ]
then
  echo "$MYSHELL not found" >&2
  exit 1
fi

jenkins=0
if [ $# -ne 0 ]
then
  if [ "$1" = "-j" ]
  then
    jenkins=1
    shift
  fi
fi

if [ $# -eq 2 ]
then
  echo "Debug mode" >&2
  echo "Shell : $MYSHELL" >&2
  echo "Reference : $REFER" >&2
  echo ""
fi

if [ $# -eq 0 ]
then
  for lst in `cat tests | grep "^\[.*\]$" | grep -vi end | sed s/'\['// | sed s/'\]'//`
  do
    path_backup=$PATH
    load_test $lst 1
    export PATH=$path_backup
  done
else
  if [ "X$1" = "X0" ]
  then
    echo "Making manifest.json"
    make_manifest > manifest.json
  else 
    if [ $# -eq 1 ]
    then
      load_test $1 0
    else
      if [ "X$1" = "X-d" ]
      then
        load_test $2 2
      else
        load_test $1 2
      fi
    fi
  fi
fi
