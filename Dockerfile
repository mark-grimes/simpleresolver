FROM busybox

ADD libraries /
ADD simpleresolver /usr/bin/

WORKDIR /data
ENTRYPOINT ["simpleresolver"]