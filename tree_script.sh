#!/bin/bash
find . -print | sed -e 's;'$(pwd)';\.;g;s;[^/]*\/;|\-\-;g;s;\-\-|; |;g'
