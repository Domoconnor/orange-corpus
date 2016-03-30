@extends('layouts.app')

@section('content')
    <div class="container">
        <h2>{{date('D d F', $timestamp)}}</h2>
        <div class="graph" id="T{{$timestamp}}">

        </div>

        <h2>Readings:</h2>
        <table class="table table-striped">
            <tr>
                <th>Time</th>
                <th>Reading</th>
                <th>Decibels</th>
            </tr>
            @foreach($readings as $reading)
                <tr>
                    <td>{{$reading['reading_time']}}</td>
                    <td>{{$reading['value']}}</td>
                    <td>{{round(20*log($reading['value']/4) + 30)}}</td>
                </tr>
            @endforeach
        </table>
    </div>

@endsection
