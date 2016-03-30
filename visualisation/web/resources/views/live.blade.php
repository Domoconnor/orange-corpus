@extends('layouts.app')

@section('content')
    <div class="container">
        <h2>Live Data</h2>
        <h2>Readings:</h2>

        <table class="table table-striped">
            <tr>
                <th>Time</th>
                <th>Reading</th>
            </tr>
           @foreach($data as $row)
               <tr>
                   <td>{{date('Y-m-d H:i:s', +$row[0]+854300)}}</td>
                   <td>{{rand(1000, 10000)}}</td>
               </tr>
               @endforeach
        </table>
    </div>

@endsection
