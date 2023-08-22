`timescale 1ns / 1ps

/*
    By ywy_c_asm
    常数定义
*/

`define MA_RIVER_SOC



`define     ICACHE_ENABLE   1
`define     DCACHE_ENABLE   1
//`define     L2_CACHE_ENABLE
`define     L1_TLB_SIZE     3

`define     CNT_EXCEPTION   16      //异常个数
//异常编码（5位）
`define E_noexception       0       //无异常
`define E_reserved          1
`define E_read_addr_error   2
`define E_read_tlb_miss     3
`define E_read_tlb_invalid  4       //取指和load共用
`define E_syscall           5
`define E_break             6
`define E_trap              7
`define E_store_addr_error  8
`define E_store_tlb_miss    9
`define E_store_tlb_invalid 10
`define E_overflow          11
`define E_copunusable       12      //CP1不可用（注意：当Status.CU1=0时将excode=12解读为这个）
`define E_fpe               12
`define E_tlb_modified      13
`define E_interrupt         14
`define E_copunusable0      15      //CP0



`define     CNT_ALUOP       16      //ALU操作种类数
//ALU编码
`define ALUOP_useB          0
`define ALUOP_add           1
`define ALUOP_sub           2
`define ALUOP_slt           3
`define ALUOP_sltu          4
`define ALUOP_and           5
`define ALUOP_lui           6
`define ALUOP_nor           7
`define ALUOP_or            8
`define ALUOP_xor           9
`define ALUOP_shl           10
`define ALUOP_shr           11
`define ALUOP_sar           12
`define ALUOP_useA          13
`define ALUOP_link          14  //取PC
`define ALUOP_zero          15  //直接置0


`define     CNT_CMP         11      //CMP种类数
//CMP编码
`define CMP_true    0
`define CMP_ne      1 
`define CMP_gez     2 
`define CMP_gtz     3 
`define CMP_lez     4 
`define CMP_ltz     5 
`define CMP_geu     6 
`define CMP_ltu     7
`define CMP_ge      8
`define CMP_lt      9
`define CMP_eq      10


`define     CNT_CTRL        38      //杂项控制信号数
//杂项控制信号
`define     CTRL_wen        0       //指令是否具有写回行为（对于movn和movz要置1）
`define     CTRL_use_rs     1       //指令是否需要使用rs
`define     CTRL_use_rt     2       //指令是否需要使用rt
`define     CTRL_is_b_imm   3       //操作数B是否为imm
`define     CTRL_is_branch  4       //是否为分支指令（包括J），需要在ALU里判断分支预测成功和计算目标地址
`define     CTRL_is_jr      5       //是否为jr/jalr
`define     CTRL_is_j       6       //是否为j/jal
`define     CTRL_checkov    7       //是否要在add或sub时检查overflow
`define     CTRL_use_sa     8       //移位时是否使用sa
`define     CTRL_trap       9       //是否为条件trap
`define     CTRL_movn       10      //是否为movn
`define     CTRL_mustflush  11      //无论如何必须在Commit时作出flush行为
`define     CTRL_wrHi       12      //是否要修改Hi
`define     CTRL_load       13      //是否为load指令
`define     CTRL_store      14      //是否为store指令
`define     CTRL_is_ret     15      //是否为ret
`define     CTRL_mtc0       16
`define     CTRL_tlbp       17
`define     CTRL_icache_hit 18
`define     CTRL_icache_index   19
`define     CTRL_tlbr       20
`define     CTRL_tlbwr      21
`define     CTRL_eret       22
`define     CTRL_tlbwi      23
`define     CTRL_wrLo       24      //是否要修改Lo
`define     CTRL_cachewb    25      //cache指令是否写回脏块
`define     CTRL_movz       26
`define     CTRL_prederr    27      //本来不是分支指令，但预测转移了
`define     CTRL_ll         28
`define     CTRL_wait       29
`define     CTRL_likely     37
//以下是FPU支持
`define     CTRL_fpu        30
`define     CTRL_nocpu      31
`define     CTRL_issue2     32      //对于MU是否要发射两条
`define     CTRL_waitfpu    33      //对于MDU保留站
`define     CTRL_waitfpubool    34  //对于MDU保留站
`define     CTRL_tofpu      35      //对于MDU和MU
`define     CTRL_ctc1       36


`define     WIDTH_other     40      //每个FU除了result之外的额外结果宽度


`define     CNT_MDUOP       16       //MDU操作种类数
//MDU操作编码（按位信号）
`define     MDUOP_mfhi      0
`define     MDUOP_mflo      1
`define     MDUOP_mthi      2
`define     MDUOP_mtlo      3
`define     MDUOP_mul       4   //操作需要s/u乘法器
`define     MDUOP_div       5   //操作需要s/u除法器   
`define     MDUOP_addHiLo   6   //是否累加HiLo
`define     MDUOP_subHiLo   7   //是否累减HiLo
`define     MDUOP_signed    8   //是否进行有符号乘除
`define     MDUOP_mfc0      9
`define     MDUOP_clo       10
`define     MDUOP_clz       11
`define     MDUOP_wb        12  //表示wen
//FPU支持
`define     MDUOP_mfc1      13
`define     MDUOP_cfc1      14
`define     MDUOP_movt      15  //不管movf/t，只要条件满足就行


`define     CNT_MUOP        15  //MU操作种类数
//MU操作编码
`define     MUOP_sb         0
`define     MUOP_sh         1
`define     MUOP_sw         2
`define     MUOP_swl        3
`define     MUOP_swr        4
`define     MUOP_lb         5
`define     MUOP_lbu        6
`define     MUOP_lh         7
`define     MUOP_lhu        8
`define     MUOP_lw         9
`define     MUOP_lwl        10
`define     MUOP_lwr        11
`define     MUOP_cacheindex 12  //基于index的cache清空
`define     MUOP_cachehit   13  //基于hit的cache清空
`define     MUOP_calcaddr   14  //仅计算地址（用于i-cache维护）并顺便翻译，计算出的paddr被写入result，也要查TLB

`define     CNT_FU          3
//用于标识指令属于哪一类
`define     FU_ALU          0
`define     FU_MU           1
`define     FU_MDU          2


`define     CNT_TLB         64       //8个TLB条目

`define     ROB_SIZE        32      //ROB为32×2

`define     STATION_ALU_SIZE    4   //ALU0/1有4个保留站
`define     STATION_MU_SIZE     3   //MU有3个保留站
`define     STATION_MDU_SIZE    2   //MDU有2个保留站

`define     BUFFER_SIZE     8       //指令Buffer容量为8×2（实际上是7×2）

`define     BTB_SIZE        256     //分支预测器有512个BTB表项
`define     History_SIZE    4096     //512个9位局部History表项


`define     CNT_INST        100
//指令编码
`define I_add       1
`define I_addi      2
`define I_addu      3
`define I_addiu     4
`define I_sub       5
`define I_subu      6
`define I_slt       7
`define I_slti      8
`define I_sltu      9
`define I_sltiu     10
`define I_div       11
`define I_divu      12
`define I_mult      13
`define I_multu     14
`define I_and       15
`define I_andi      16
`define I_lui       17
`define I_nor       18
`define I_or        19
`define I_ori       20
`define I_xor       21
`define I_xori      22
`define I_sllv      23
`define I_sll       24
`define I_srav      25
`define I_sra       26
`define I_srlv      27
`define I_srl       28
`define I_beq       29
`define I_bne       30
`define I_bgez      31
`define I_bgtz      32
`define I_blez      33
`define I_bltz      34
`define I_bgezal    35
`define I_bltzal    36
`define I_j         37
`define I_jal       38
`define I_jr        39
`define I_jalr      40
`define I_mfhi      41
`define I_mflo      42
`define I_mthi      43
`define I_mtlo      44
`define I_break     45
`define I_syscall   46
`define I_lb        47
`define I_lbu       48
`define I_lh        49
`define I_lhu       50
`define I_lw        51
`define I_sb        52
`define I_sh        53
`define I_sw        54
`define I_eret      55
`define I_mfc0      56
`define I_mtc0      57
`define I_cache     58
`define I_tlbwi     59
`define I_tlbr      60
`define I_tlbp      61
`define I_clo       62
`define I_clz       63
`define I_madd      64
`define I_maddu     65
`define I_msub      66
`define I_msubu     67
`define I_mul       68
`define I_ll        69
`define I_lwl       70
`define I_lwr       71
`define I_pref      72
`define I_sc        73
`define I_swl       74
`define I_swr       75
`define I_sync      76
`define I_movn      77
`define I_movz      78
`define I_teq       79
`define I_teqi      80
`define I_tge       81
`define I_tgei      82
`define I_tgeiu     83
`define I_tgeu      84
`define I_tlt       85
`define I_tlti      86
`define I_tltiu     87
`define I_tltu      88
`define I_tne       89
`define I_tnei      90
`define I_beql      91
`define I_bgezall   92
`define I_bgezl     93
`define I_bgtzl     94
`define I_blezl     95
`define I_bltzall   96
`define I_bltzl     97
`define I_bnel      98
`define I_tlbwr     99
`define I_wait      100

`define CNT_INST_EX 12

`define I_ex_cfc1   0
`define I_ex_ctc1   1
`define I_ex_mfc1   2
`define I_ex_mtc1   3
`define I_ex_lwc1   4
`define I_ex_ldc1   5
`define I_ex_swc1   6
`define I_ex_sdc1   7
`define I_ex_movf   8
`define I_ex_movt   9
`define I_ex_movn   10
`define I_ex_movz   11


`define ICache_index_SIZE   64
`define DCache_index_SIZE   64
`define ICache_block_WORDS  16
`define DCache_block_WORDS  16


`define SPEF_CNT    4
`define SPEF_NAN    0
`define SPEF_INF    1
`define SPEF_ZERO   2
`define SPEF_DENORM 3   //非规格数（包括0）

//舍入模式
`define ROUND_NEAR  0
`define ROUND_ZERO  1
`define ROUND_FLOOR 3
`define ROUND_CEIL  2

//浮点运算控制字
`define FPUCTRL_CNT     19
`define FPUCTRL_DIRECT  0       //单周期FPU指令（abs/mov/neg）
`define FPUCTRL_ABS     1       //abs,清空sign
`define FPUCTRL_NEG     2       //neg,取反sign
`define FPUCTRL_ADD     3       //add/sub
`define FPUCTRL_SUB     4       //sub,将操作数b取反
`define FPUCTRL_MUL     5       
`define FPUCTRL_DIV     6
`define FPUCTRL_SQRT    7
`define FPUCTRL_CINT    8       //取整（ceil,cvt.w,floor,round,trunc）
`define FPUCTRL_CVTW    9       //cvt.w，使用FCSR定义的舍入模式
`define FPUCTRL_CFNUM   10      //定点数转浮点数
`define FPUCTRL_OPSNG   11      //操作数是否为single
`define FPUCTRL_RESSNG  12      //结果是否为single（取f_round的正确的输出）
`define FPUCTRL_CAST    13      //single和double互转（我们将其视作b=0的add）
`define FPUCTRL_MOVN    14
`define FPUCTRL_MOVZ    15
`define FPUCTRL_TOHIGH  16      //对于32位结果，将其输出到result的高32位上（针对奇fd）
`define FPUCTRL_MOVMDU  17
`define FPUCTRL_MOVMU   18

//浮点指令编码
`define FI_abs          0
`define FI_add          1
`define FI_bc1f         2
`define FI_bc1t         3
`define FI_ccond        4
`define FI_ceil         5
`define FI_cvtd         6
`define FI_cvts         7
`define FI_cvtw         8
`define FI_div          9
`define FI_floor        10
`define FI_ldc1         11
`define FI_lwc1         12
`define FI_mfc1         13
`define FI_mov          14
`define FI_movf         15
`define FI_movn         16
`define FI_movt         17
`define FI_movtfmt      18
`define FI_movz         19
`define FI_mtc1         20
`define FI_mul          21
`define FI_neg          22
`define FI_round        23
`define FI_sdc1         24
`define FI_sqrt         25
`define FI_sub          26
`define FI_swc1         27
`define FI_trunc        28
`define FI_movffmt      29

`define FPU_INST_CNT    30

//浮点一般性控制信号
`define FPU_G_WEN0      0       //是否将结果低32位写回奇FPR
`define FPU_G_WEN1      1       //是否将结果高32位写回偶FPR
`define FPU_G_JUMP      2       //是否为浮点分支指令（用于处理浮点分支预测失败/维护bp）
`define FPU_G_WRITECC   3       //是否要修改FCC（C.cond）
`define FPU_G_RI        4       //保留指令

`define FPU_GLOBAL_CNT  5

//浮点异常字
`define FPE_INVALID         0
`define FPE_OVERFLOW        1
`define FPE_UNDERFLOW       2
`define FPE_DIVIDEBYZERO    3

`define FPECNT              4


//FCCU控制信号
`define FCCUCTRL_CMP        0
`define FCCUCTRL_BRANCH     1   //bc1f/bc1t
`define FCCUCTRL_FALSE      2   //bc1f/movf (为了对条件取反)
`define FCCUCTRL_TOCPU      3   //movf/movt将FCC传送到CPU
`define FCCUCTRL_CMOV       4   //movf/movt.fmt (条件传送)
`define FCCUCTRL_OPSNG      5   //仅供c.cond使用
`define FCCUCTRL_TOHIGH     6   //将32位结果输出至result高32位

`define FCCUCTRL_CNT        7


//DSP支持
//`define IMUL_USE_DSP     
`define FMUL_USE_DSP    

//FPU支持
`ifdef MA_RIVER_SOC         
    `define FPU_ENABLED
`else
    //`define FPU_ENABLED
`endif


//FPU指令信息字（与执行无关）
`define FINFO_WEN0          0
`define FINFO_WEN1          1
`define FINFO_USEFS0        2
`define FINFO_USEFS1        3
`define FINFO_USEFT0        4
`define FINFO_USEFT1        5
`define FINFO_FCCINST       6
`define FINFO_WAITFORMU     7   //需要在FPU保留站等待MU，得到操作数fs
`define FINFO_WAITFORMDU    8   //需要在FPU保留站等待MDU，得到操作数fs
`define FINFO_TOMU          9   //发射时将fs操作数值发给MU
`define FINFO_TOMDU         10  //发射时将fs操作数值发给MU

`define FINFOCNT            11

`define STATION_FPU_SIZE    4
`define STATION_FCCU_SIZE   4