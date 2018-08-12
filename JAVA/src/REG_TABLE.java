import java.util.EnumMap;
import java.util.Vector;

public class REG_TABLE {
    class ONE_REG{
        public Parameters.REGISTER m_reg;
        public int m_write_pc;
        public int m_read_pc;
        ONE_REG(Parameters.REGISTER reg){
            m_reg = reg;
            m_write_pc = m_read_pc = -1;
        }
    }
    Vector<ONE_REG> m_occ_reg_vec;

    REG_TABLE(){
        m_occ_reg_map = new EnumMap<>(Parameters.REGISTER.class);
        for(Parameters.REGISTER reg : Parameters.REGISTER.values()){
            m_occ_reg_map.add(reg,false);
        }
    }


    public boolean get_reg_state(Parameters.REGISTER reg){
        return m_occ_reg_map.get(reg);
    }

    public void set_reg_state(Parameters.REGISTER reg){
        m_occ_reg_map.put(reg,true);
    }

    public void clr_reg_state(Parameters.REGISTER reg){
        m_occ_reg_map.put(reg,false);
    }


}
