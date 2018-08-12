

public class INSTRUCTION {
    public Parameters.INS_OP m_op;
    public Parameters.REGISTER m_dst;
    public Parameters.REGISTER m_src1;
    public Parameters.REGISTER m_src2;

    public Parameters.FUNC_UNIT m_occ_func;

    //begin time = issue time
    public int m_issue_time;
    public int m_oc_time;
    public int m_ex_time;
    public int m_wb_time;
    public int m_ins_cycle;
    public boolean m_is_ex;



    public boolean is_active(){
       return m_is_ex || (m_issue_time!=0&&m_wb_time==0);
    }



    INSTRUCTION(String one_line){
        String [] ins_arr = one_line.split(",|，|\\s+");
        m_op = Parameters.INS_OP.valueOf(ins_arr[0]);
        m_dst = Parameters.REGISTER.valueOf(ins_arr[1]);
        m_src1 = Parameters.REGISTER.valueOf(ins_arr[2]);
        m_src2 = Parameters.REGISTER.valueOf(ins_arr[3]);
        m_issue_time = 0;
        m_oc_time = 0;
        m_ex_time = 0;
        m_wb_time = 0;
        m_is_ex = false;
        m_occ_func = Parameters.FUNC_UNIT.NULL;

        m_ins_cycle = Parameters.INS_EX_CYCLE_MAP.get(m_op);
    }



    @Override
    public String toString(){
        return "OP: "+m_op+"dst: " + m_dst+"src1: " + m_src1+"src2: " + m_src2;
    }

}




