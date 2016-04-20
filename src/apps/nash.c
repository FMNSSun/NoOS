#include "nash.h"
#include "../nlib/nvideo.h"
#include "../nlib/nsyscalls.h"
#include "../nlib/ntextio.h"
#include "../nlib/nstring.h"
#include "../nlib/nconv.h"
#include "../nlib/nmem.h"

NUSHORT video_driver = 0;
NCHAR nash_buffer[256];

NVALUE nash_terminate(NPVALUE ptr) {
  struct NCOLOREDTEXT text_struct;
  text_struct.text = "Can't terminate nash\r\n";
  text_struct.color = 0xF;
  nvid_print_text(text_struct);
}

NVALUE nash_print_welcome() {
  ntio_set_text_color(0xF);
  ntio_print("Welcome to No! A Shell!! (c) Roman Muentener\r\n\r\n");
}

NPCHAR nash_get_cmd() {
  ntio_print(":> ");
  ntio_set_text_color(0x7);
  ntio_read_line((NPCHAR)&nash_buffer,256,1);
  ntio_set_text_color(0xF); ntio_print("\r\n");
  return (NPCHAR)&nash_buffer;
}

NVALUE nash_process_cmd(NPCHAR cmd) {
  ntio_print("["); ntio_print(cmd); ntio_print("]\r\n");
  if(nstrcmp(cmd,"help")  == 1) {
    ntio_print("help             show help\r\n");
    ntio_print("memaa            show memory average alloc\r\n");
    ntio_print("memu             show memory usage\r\n");
    ntio_print("memd             show dead memory\r\n");
    ntio_print("memac            show memory alloc count\r\n");
  }
  else if(nstrcmp(cmd,"memaa") == 1) {
    NUSHORT mem_sid = syscall_srvc_get_id("memory");
    NINT alloc = 0;
    syscall_rpc_call_func("mem_get_average_alloc",mem_sid,(NPVALUE)&alloc);
    ntio_print("Mem Average Alloc: "); ntio_print(nitoa(alloc,10));
  }
  else if(nstrcmp(cmd,"memu") == 1) {
    NUSHORT mem_sid = syscall_srvc_get_id("memory");
    NBIGSIZE usage = 0;
    syscall_rpc_call_func("mem_get_usage",mem_sid,(NPVALUE)&usage);
    NCHAR buffer[50];
    nultoa(usage, 10, (NPCHAR)&buffer);
    ntio_print("Mem Usage: "); ntio_print(buffer);
  }
  else if(nstrcmp(cmd,"memd") == 1) {
    NUSHORT mem_sid = syscall_srvc_get_id("memory");
    NBIGSIZE dead = 0;
    syscall_rpc_call_func("mem_get_dead",mem_sid,(NPVALUE)&dead);
    NCHAR buffer[50];
    nultoa(dead, 10, (NPCHAR)&buffer);
    ntio_print("Mem Dead: "); ntio_print(buffer);
  }
  else if(nstrcmp(cmd,"memac") == 1) {
    NUSHORT mem_sid = syscall_srvc_get_id("memory");
    NBIGSIZE allocs = 0;
    syscall_rpc_call_func("mem_get_allocs",mem_sid,(NPVALUE)&allocs);
    NCHAR buffer[50];
    nultoa(allocs, 10, (NPCHAR)&buffer);
    ntio_print("Mem Allocs: "); ntio_print(buffer);
  }
  else if(nstrcmp(cmd,"about") == 1) {
    ntio_print("NoOS (c) Roman Muentener 2009\r\nnash is not a shell!!");
  }
  else if(nstrcmp(cmd,"srvcdmp") == 1) {
    NUSHORT srvc_sid = syscall_srvc_get_id("service");
    syscall_rpc_call_func("srvc_dump",srvc_sid,(NPVALUE)NULL);
  }
  else if(nstrcmp(cmd,"rpcdmp") == 1) {
    NUSHORT rpc_sid = syscall_srvc_get_id("rpc");
    syscall_rpc_call_func("rpc_dump",rpc_sid,(NPVALUE)NULL);
  }
  else if(nstrcmp(cmd,"memtest") == 1) {
    NPVALUE ptr = nmemalloc(3777);
    nmemfree(ptr);
  } 
  else if(nstrcmp(cmd,"fakeerror") == 1) {
    int volatile bar = 1;
    int volatile foo = (42 / (1 - bar));
    if(foo) ntio_print("fakeerror");
  }
  else if(nstrcmp(cmd,"kend") == 1) {
    char buffer[32];
    nultoa((NULONG)&kernel_end,16,(NPCHAR)&buffer);
    ntio_print((NPCHAR)&buffer);
  } 
  else if(nstrcmp(cmd,"clear") == 1) {
    nvid_clear_screen();
    nvid_set_row(0);
  }
  ntio_print("\r\n");
}

NVALUE nash_start() {
  nvid_init();
  ntio_init();
  nmem_init();
  NUSHORT nash_id = syscall_srvc_register_service("nash");
  syscall_rpc_register_func("nash_terminate",(NPVALUE)nash_terminate,nash_id);

  nash_print_welcome();
  while(1) { 
    NPCHAR cmd = nash_get_cmd(); 
    nash_process_cmd(cmd);
  }

  syscall_rpc_call_func("nash_terminate",nash_id,(NPVALUE)0);
  while(1){}
}


