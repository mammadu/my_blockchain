# my_blockchain

TODO:

Implement sync command

Check syncstatus after every command

remove_block needs to print out "5: block doesn't exist" when removing a block that doesn't exist

when calling sync, nodes get new blocks... we didn't code that...
After calling sync, calling ls -l creates a segfault

Debug blocks* duplicate_block_list(blocks* head) segfaulting due to a read memory access.
    This is most likely due to sync_blocks overwriting the values of the blocks at each node