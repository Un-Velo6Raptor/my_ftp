#!/bin/bash
 
if [ "$#" -ne 2 ]; then
    echo "USAGE: $0 host port"
    exit 0
fi
 
USERNAME="Anonymous"
PASS=""
 
RED='\033[0;31m'
GREEN='\033[0;32m'
WHITE='\033[m' # No Color
 
HOST=$1
PORT=$2
MKFIFO=`which mkfifo`
PIPE=fifo
OUT=outfile
TAIL=`which tail`
NC="`which nc` -C"
TIMEOUT=1 #max time before reading server response
 
 
getcode()
{
  sleep $TIMEOUT
  local code=$1
  echo "Waiting for $code reply-code"
  local data=`$TAIL -n 1 $OUT |cat -e |grep "^$code.*[$]$" |wc -l`
  return $data
}
 
print_failed()
{
    echo "$1 test failed"
    echo "Expected reply-code: $2"
    echo "Received : ["`$TAIL -n 1 $OUT| cat -e`"]"
    echo -e "${RED}KO${WHITE}"
}
 
print_succeeded()
{
  echo "$1 test succeeded"
  echo -e "${GREEN}OK${WHITE}"
  kill_client 2>&1 >/dev/null
}
 
launch_client()
{
  local host=$1
  local port=$2
 
  $MKFIFO $PIPE
  ($TAIL -f $PIPE 2>/dev/null | $NC $host $port &> $OUT &) >/dev/null 2>/dev/null
 
  echo "Connecting to $host : $port"
  sleep $TIMEOUT
  getcode 220
  if [[ $? -eq 1 ]]; then
    echo -e "Reply-code ${GREEN}OK${WHITE}"
    return 1
  else
    echo "Connection to $host:$port failed"
    echo "Expected reply-code: 220"
    echo "Received : ["`tail -n 1 $OUT |cat -e`"]"
    return 0
  fi
}
 
launch_test()
{
  local test_name=$1
  local cmd=$2
  local code=$3
 
  echo "##########  ${test_name}  ##########"
  echo "Sending [$cmd^M$]"
  echo "$cmd" >$PIPE
  getcode $code
  if [[ ! $? -eq 1 ]]; then
    print_failed "$test_name" "$code"
  else
    echo -e "Reply-code ${GREEN}OK${WHITE}"
  fi
}
 
kill_client()
{
  local nc=`which nc`
 
  if [ `pidof $TAIL | wc -l` -ne 0 ]
  then
    killall $TAIL &>/dev/null
  fi
  if [ `pidof $nc | wc -l` -ne 0 ]
  then
    killall $nc &>/dev/null
  fi
  rm -f $PIPE $OUT &> /dev/null
}
 
clean()
{
  rm -f $PIPE $OUT log &>/dev/null
}
 
rm -f   fifo
rm -rf test
 
launch_client $HOST $PORT
if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
fi
 
launch_test "NO LOG NOOP" "NOOP" 200
launch_test "NO LOG CWD directory exist" "CWD test" 530
launch_test "NO LOG CDUP" "CDUP" 530
launch_test "NO LOG CWD directory doesn't exist" "CWD test" 530
launch_test "NO LOG DELE file exist" "DELE test" 530
launch_test "NO LOG DELE file doesn't exist" "DELE test" 530
launch_test "NO LOG PWD" "PWD" 530
launch_test "NO LOG HELP" "HELP" 214
 
launch_test "PASS before USER" "PASS " 503
launch_test "USER" "USER Test" 331
launch_test "PASS" "PASS " 530
launch_test "USER" "USER Anonymous" 331
launch_test "PASS" "PASS " 230
launch_test "NOOP" "NOOP" 200
mkdir test
launch_test "CWD directory exist" "CWD test" 250
launch_test "CDUP" "CDUP" 200
rmdir test
launch_test "CWD directory doesn't exist" "CWD test" 550
touch test
launch_test "DELE file exist" "DELE test" 250
launch_test "DELE file doesn't exist" "DELE test" 550
launch_test "PWD" "PWD" 257
launch_test "HELP" "HELP" 214
launch_test "QUIT" "QUIT" 221
clean
