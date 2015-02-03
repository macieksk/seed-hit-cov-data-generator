sed 's/\\n/\n/g;s/{"stdout":"/\n{"stdout":\n/g;s/"}/\n}/g;s/\([[:alnum:]]\{8\}-[[:alnum:]]\{4\}-[[:alnum:]]\{4\}-[[:alnum:]]\{4\}-[[:alnum:]]\{12\}\)/\n>>>>>>>>>>>\n/g;s/\\"/"/g;s/\\t/\t/g' $*
