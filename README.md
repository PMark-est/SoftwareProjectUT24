# Korp corpus annotation system

## Setting up cwb

In the cwb folder create a directory 'corpora'. Go into that folder and create two more directories 'data' and 'registry'. Add the vrt file into the data directory. After that
1. ``
cwb-encode -d absolute/path/to/data -f absolute/path/to/data/universal_dev.vrt -R absolute/path/to/registry/universal -P pos -P lemma -S s -S text:title -c utf8
``
2. ``cwb-makeall -r absolute/path/to/registry universal``

The steps above assume the provided vrt file is used. 
