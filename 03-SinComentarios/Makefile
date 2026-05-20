.PHONY: runV1 runV2 clean

runV1: RemoveCommentsV1
	time ./RemoveCommentsV1 < Test.c > NoCommentsV1.c 

runV2: RemoveCommentsV2
	time ./RemoveCommentsV2 < Test.c > NoCommentsV2.c 

RemoveCommentsV1: RemoveCommentsV1.c

RemoveCommentsV2: RemoveCommentsV2.c

clean:
	rm RemoveCommentsV1 RemoveCommentsV2 NoCommentsV1.c NoCommentsV2.c