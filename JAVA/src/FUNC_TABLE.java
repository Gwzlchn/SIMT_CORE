import java.util.Vector;

public class FUNC_TABLE {
    public enum FUNC_UNIT_STAGE{
        Busy,Op,Fi,Fj,Fk,Qj,Qk,Rj,Rk
    }
    private Vector<Vector<Integer>> m_func_table;

    FUNC_TABLE(){
        int func_cnt = Parameters.FUNC_UNIT.getSize();
        m_func_table = new Vector<>(func_cnt);
        for(int i =0;i!= func_cnt;i++){
            m_func_table.add(i, new Vector<Integer>(FUNC_UNIT_STAGE.values().length));

        }
    }

    boolean is_func_unit_valid(Parameters.FUNC_UNIT to_occ){
        return m_func_table.get(to_occ.ordinal()).get(FUNC_UNIT_STAGE.Busy.ordinal()) == 0;
    }

    boolean occupy_func_table_one_ins(Parameters.FUNC_UNIT to_occ,INSTRUCTION one_ins){

        int func = to_occ.ordinal();
        if(m_func_table.get(func).get(FUNC_UNIT_STAGE.Busy.ordinal()) == 0)
            return false;

        m_func_table.get(func).set(FUNC_UNIT_STAGE.Busy.ordinal(), 1);
        m_func_table.get(func).set(FUNC_UNIT_STAGE.Op.ordinal(), one_ins.m_op.ordinal());
        m_func_table.get(func).set(FUNC_UNIT_STAGE.Fi.ordinal(), one_ins.m_dst.ordinal());
        m_func_table.get(func).set(FUNC_UNIT_STAGE.Fj.ordinal(), one_ins.m_src1.ordinal());
        m_func_table.get(func).set(FUNC_UNIT_STAGE.Fk.ordinal(), one_ins.m_src2.ordinal());
        m_func_table.get(func).set(FUNC_UNIT_STAGE.Rk.ordinal(), 0);
        m_func_table.get(func).set(FUNC_UNIT_STAGE.Rj.ordinal(), 0);
        return true;
    }

    int get_pipeline_time(Parameters.FUNC_UNIT now_func,int threads_per_warp){
        if(threads_per_warp == 0)
            return 0;
        int now_op_cnt = Parameters.FUNC_UNIT_CNT_MAP.get(now_func);
        double extra_time = threads_per_warp / (double)now_op_cnt - 1;
        return (int) Math.ceil(extra_time);
    }

    boolean find_func_unit_valid(Parameters.INS_OP ins_op, Parameters.FUNC_UNIT to_occ){
        return true;
    }





}
