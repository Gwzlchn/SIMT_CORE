
import java.util.EnumMap;




public class Parameters {

    public enum REGISTER{
        F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,R0,R1,R2,R3,R4
    };

    //NULL 是未分配
    public enum FUNC_UNIT{
        NULL,SFU1, MEMPIPE1, SFU2, SFU3, SP1, SP2, SP3, SP4;
        public static int getSize(){
            return FUNC_UNIT.values().length;
        }
    };

    public enum INS_OP{
        LD, ST, MULTD, SUBD, DIVD, ADDD
    };

    public static EnumMap<INS_OP,Integer> INS_EX_CYCLE_MAP = new EnumMap<INS_OP, Integer>(INS_OP.class){{
        put(INS_OP.LD,2);
        put(INS_OP.ST,4);
        put(INS_OP.MULTD,20);
        put(INS_OP.DIVD,40);
        put(INS_OP.ADDD,2);
        put(INS_OP.SUBD,10);
    }};

    public static EnumMap<FUNC_UNIT,Integer> FUNC_UNIT_CNT_MAP = new EnumMap<FUNC_UNIT, Integer>(FUNC_UNIT.class){{
        put(FUNC_UNIT.MEMPIPE1,32);
        put(FUNC_UNIT.SFU1,32);
        put(FUNC_UNIT.SFU2,16);
        put(FUNC_UNIT.SFU3,16);
        put(FUNC_UNIT.SP1,16);
        put(FUNC_UNIT.SP2,16);
        put(FUNC_UNIT.SP3,16);
        put(FUNC_UNIT.SP4,16);
    }};

}
