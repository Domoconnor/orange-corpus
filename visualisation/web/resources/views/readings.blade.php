@extends('layouts.app')

@section('content')
    <div class="container">
        <div class="row">
            <div class="col-md-12">
                @foreach($data as $day)
                    <a href="/day/{{$day->start}}">
                        <div class="col-md-3">
                            <div class="panel panel-default">
                                <div class="panel-heading">
                                    <h3 class="panel-title">{{date("D M j", $day->start)}}</h3>
                                </div>
                                <div class="panel-body">
                                    <svg class='chart' id="D{{date("Y-m-d", $day->start)}}" style='display: block; margin: auto;'></svg>
                                    <p>High: {{$day->max}}</p>
                                    <p>Low: {{$day->min}}</p>
                                </div>
                            </div>
                        </div>
                    </a>
                @endforeach
            </div>
        </div>
    </div>
@endsection
