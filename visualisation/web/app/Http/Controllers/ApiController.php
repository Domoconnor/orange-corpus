<?php

namespace App\Http\Controllers;

use App\Device;
use App\Reading;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;
use App\Http\Requests;

class ApiController extends Controller
{
    public function readings(Request $request)
    {

        $device = Device::find(1);

        $data = $request->input('data');
        $data = explode('\n', $data);
        $data = array_map('str_getcsv', $data);
        $batt = 0;

        //Change colum names
        foreach($data as $k => $v)
        {
            if($data[$k][0] == "batt")
            {
                $batt = $v[1];
                unset($data[$k]);
            }
            else
            {
                $data[$k][0] = $data[$k][0] + 604800;
                $random = rand(0,4)-2;
                $data[$k][1] += $random;
                $reading = new Reading(['reading_time' => date('Y-m-d H:i:s', $data[$k][0]), 'value' => $data[$k][1]]);
                $device->readings()->save($reading);
            }
        }

        return response()->json(["status" => "success"], 200);
    }


    public function get_hourly_averages($start = 0, $end = 0)
    {
        if ($end == 0)
        {
            $end = date("Y-m-d");
        } else {
            $end = date("Y-m-d", $end);
        }

        $start = date("Y-m-d", $start);
        $query = "SELECT date_trunc('hour', reading_time - INTERVAL '1 minute') AS start,
                    date_trunc('hour',reading_time - INTERVAL '1 minute')  + INTERVAL '1 hours' AS end,
                    avg(value)
                    FROM readings
                    WHERE reading_time BETWEEN :start AND :end
                    GROUP BY date_trunc('hour', reading_time - INTERVAL '1 minute')
                    ORDER BY start";

        $averages = DB::select($query, ['start' => $start, 'end' => $end]);

        return response()->json($averages, 200);
    }

    function get_clock_averages()
    {
        $query = "SELECT avg FROM(
                    SELECT date_trunc('hour', reading_time - INTERVAL '1 minute') AS start,
                    date_trunc('hour', reading_time - INTERVAL '1 minute')  + INTERVAL '1 hours' AS end,
                    avg(value)
                    FROM readings
                    WHERE reading_time < CURRENT_DATE
                    GROUP BY date_trunc('hour', reading_time - INTERVAL '1 minute')
                    ORDER BY start) AS avg";

        $averages = DB::select($query);

        $return_string = '?';
        foreach($averages as $avg)
        {
            $return_string .= (string) round($avg->avg);
            $return_string .= ',';
        }
        $return_string = rtrim($return_string, ',');
        $return_string .= '!';

        return $return_string;
    }
}
