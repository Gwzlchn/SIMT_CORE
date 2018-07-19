import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Vector;

class One_Instruction {
    private String one_line = new String("");
    private ArrayList<String> one_ins = new ArrayList<>();

    public One_Instruction(String one_line) throws Exception {

        this.one_line = one_line;
        String[] str_arr = one_line.split(" ", 2);
        one_ins.add(str_arr[0]);
        String[] op_arr = str_arr[1].split(",");
        for (String i : op_arr)
            one_ins.add(i);

        if (one_ins.size() != 4)
            throw new Exception(one_line + "指令读取有误");
    }

    @Override
    public String toString() {
        return one_line;
    }
}


public class Instructions{

    private Vector<One_Instruction> all_ins = new Vector<>();

    public Instructions(String file_name){
        read_ins_from_text(file_name);
    }

    public void read_ins_from_text(String file_name){
        File file = new File(file_name);
        try {
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String tempString = new String();
            // 一次读入一行，直到读入null为文件结束
            while ((tempString = reader.readLine()) != null) {
                try {
                    System.out.println(tempString);
                    One_Instruction one_ins = new One_Instruction(tempString);
                    all_ins.add(one_ins);
                }catch (Exception e){
                    e.printStackTrace();
                }


            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }



    @Override
    public String toString() {
        StringBuilder str_all_ins = new StringBuilder();
        for(One_Instruction one : all_ins) {
            str_all_ins.append(one);
            str_all_ins.append('\n');
        }

        return  str_all_ins.toString();
    }
}
