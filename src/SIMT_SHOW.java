import javax.swing.*;

public class SIMT_SHOW {

    private String ins_file = "ptx_ins.txt";

    private JPanel m_outside_lanel;
    private JButton m_next_cycle_btn;
    private JButton m_reset_btn;
    private JButton m_ld_ptx_btn;
    private JTextArea m_simt_text;
    private JButton m_ld_mem_btn;
    private JTable m_i_cache_table;
    private JTextArea m_i_cache_text;
    private JTextArea m_i_buf_text;
    private JTable m_i_buf_table;
    private JTextArea m_score_text;
    private JTable m_score_table;
    private JTextArea m_reg_text;
    private JTable m_reg_table;
    private JTextArea m_op_col_text;
    private JTable m_op_col_table;
    private JTable m_mem_table;
    private JTextArea m_mem_text;
    private JLabel m_now_cycle_label;
    private JPanel m_header_panel;
    private JPanel m_consist_panel;


    private I_CACHE m_i_cache = new I_CACHE(ins_file);

    public SIMT_SHOW() {
        m_next_cycle_btn = new JButton();



    }
    private void init_state(){

        m_i_cache_table = m_i_cache.init_i_cache_table();

    }
    private void update_state(){

    }


}
