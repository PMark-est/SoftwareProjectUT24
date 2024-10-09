# Korp corpus annotation system

## Setting up cwb

In the cwb folder create a directory 'corpora'. Go into that folder and create two more directories 'data' and 'registry'. Add the vrt file into the data directory. After that
1. ``
cwb-encode -d absolute/path/to/corpus/data -f absolute/path/to/corpus/data/universal_dev.vrt -R absolute/path/to/registry/universal -S corpus -S text -S sentence -c utf8
``
2. ``cwb-makeall -r absolute/path/to/registry universal``

The steps above assume the provided vrt file is used. 
