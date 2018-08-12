import java.util.Vector;


//一个warp内所有指令，每周期前推
public class ONE_WARP {
    private Vector<INSTRUCTION> m_one_warp_all_ins;
    private int m_threads_this_warp;
    private int m_warp_id;

    ONE_WARP(String file_name,int threads_this_warp,int warp_id){
        READ_FILE one_warp = new READ_FILE(file_name);
        m_one_warp_all_ins = one_warp.get_ins();

        m_threads_this_warp = threads_this_warp;
        m_warp_id = warp_id;
    }

    public void ins_buffer_to_issue_input(){
        if()
    }
}
