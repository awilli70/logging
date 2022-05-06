#include <linux/bpf.h>
#include <bpf_helpers.h>

#ifdef BPF_RW
    #define RET XDP_PASS
#else 
    #define RET 0
#endif

SEC("logging")
int _control_logging(void *ctx){
    
}