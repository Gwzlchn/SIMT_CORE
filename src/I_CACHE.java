import javax.swing.*;

public class I_CACHE {

    private Instructions all_ins;
    private JTable I_Cache_Table;
    public I_CACHE(String file_name){
        read_from_txt(file_name);

    }
    public void read_from_txt(String file_name){
        all_ins = new Instructions(file_name);

    }
    public JTable init_i_cache_table(){

    }
    public JTable update_i_cache_table(){

    }



}

