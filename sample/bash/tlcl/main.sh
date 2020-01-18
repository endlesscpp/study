#!/bin/bash

# Program to output a system information page

TITLE="System Information Report For $HOSTNAME"
CURRENT_TIME=$(date +"%x %r %Z")
TIME_STAMP="Generated $CURRENT_TIME, by $USER"

function report_uptime {
    cat <<- _EOF_
    <H2>System Uptime</H2>
    <PRE>$(uptime)</PRE>
_EOF_
return
}

function report_disk_space {
    cat <<- _EOF_
    <H2>Disk Space Utilization</H2>
    <PRE>$(df -h)</PRE>
_EOF_
return
}

function report_home_space {
    if [[ $(id -u) -eq 0 ]]; then
    cat <<- _EOF_2
    <H2>Home Space Utilization</H2>
    <pre>$(du -sh /home/*)<pre>
_EOF_2
else
    cat <<- _EOF_2
    <H2>Home Space Utilization</H2>
    <pre>$(du -sh $HOME)<pre>
_EOF_2
    fi
    return
}

cat <<- _EOF_
<HTML>
    <HEAD>
        <TITLE>$TITLE</TITLE>
    </HEAD>
    <BODY>
        <H1>$TITLE</H1>
        <P>$TIME_STAMP</P>
        $(report_uptime)
        $(report_disk_space)
        $(report_home_space)
    </BODY>
</HTML>
_EOF_

