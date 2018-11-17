#!/usr/bin/env ruby
require 'Faker'

args = ARGV
valid_inputs = %w{name telephone social salary}

def is_numeric?(obj)
   obj.to_s.match(/\A[+-]?\d+?(\.\d+)?\Z/) == nil ? false : true
end
def is_file_name?(obj)
   obj.to_s.match(/\w+(\.\w+)\Z/) == nil ? false : true
end

#call this:
#ruby #{this_file_name} -n=number_of_records args={account_number, balance}

filename = "/Users/christianmeyer/cpp/ch9/P9_11/db"
if is_file_name?(ARGV[ARGV.size-1].to_s)
    filename = ARGV[ARGV.size-1].to_s
end
File.open(filename, 'w') { |f|
    if (ARGV.size > 2)
        puts "generating data..."
    end
    n = 20
    number_given = 0
    file_given = 0
    if is_numeric?(args[0])
        n = args[0].to_i
        number_given = 1
    end
    if is_file_name?(ARGV[ARGV.size-1].to_s)
        filename = ARGV[ARGV.size-1].to_s
        file_given = 1
    end
    n.times do
        num_args = ARGV.size - number_given - file_given
        print_line = "";
        args.any? {|arg|
            if arg == "account_number"
                #account_no = ('%8.8s\.%2.2s' % (rand(1000000).to_s, rand().to_s).ljust(10);
                account_no = ('%10.10s' % rand(1000000000...10000000000))
                print_line += account_no
                num_args -= 1
                if num_args > 0
                    print_line += "|"
                end
            end
            if arg == "balance"
                bal = '$%-9.2f' % (rand(1000000) + rand())
                print_line += bal
                num_args -= 1
                if num_args > 0
                    print_line += "|"
                end
            end
        }
        print_line += "\n"
        if print_line.length > 1
            f.write(print_line)
        end
    end
}
