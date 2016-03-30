<?php

namespace App\Http\Controllers;

use App\Device;
use App\Reading;
use Illuminate\Foundation\Bus\DispatchesJobs;
use Illuminate\Routing\Controller as BaseController;
use Illuminate\Foundation\Validation\ValidatesRequests;
use Illuminate\Foundation\Auth\Access\AuthorizesRequests;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use DB;

class Controller extends BaseController
{
    use AuthorizesRequests, DispatchesJobs, ValidatesRequests;

    public function update(Request $request)
    {
        $user = Auth::user();
        $user->phone = $request->phone;
        $user->email = $request->email;
        $user->save();

        return back();
    }

    public function sensor()
    {
        $sensors = Device::all();

        return view('sensors', ['sensors' => $sensors]);
    }

    public function show_readings()
    {
        $query = "SELECT start, max, min FROM(
                    SELECT date_trunc('day', reading_time - INTERVAL '1 minute') AS start,
                    date_trunc('day', reading_time - INTERVAL '1 minute')  + INTERVAL '1 days' AS end,
                    max(value),
                    min(value)
                    FROM readings
                    WHERE reading_time < CURRENT_DATE
                    GROUP BY date_trunc('day', reading_time - INTERVAL '1 minute')
                    ORDER BY start) AS max";
        $averages = DB::select($query);

        foreach($averages as $average)
        {
            $average->start = strtotime($average->start);
        }
        return view('readings',['data' => $averages]);
    }

    public function show_day($timestamp)
    {
        $data = Reading::whereBetween('reading_time', [date("Y-m-d H:i:s", $timestamp), date("Y-m-d H:i:s", ($timestamp + 84000))])->get();
        return view('day', ['timestamp' => $timestamp, 'readings' => $data]);
    }

    public function show_compare()
    {
        return view('compare');
    }

    public function live()
    {
        $data = file_get_contents('http://178.62.43.107/orange/api/get?key=611f13f1-92ac-4b28-9f38-0834a8ee67bd');
        $data = explode("!", $data);

        foreach($data as &$in)
        {
            $new = explode("batt", $in);
            $in = explode(',', $new[0]);

        }
        return view('live', ['data' => $data]);
    }
}
