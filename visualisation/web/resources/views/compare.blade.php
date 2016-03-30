@extends('layouts.app')

@section('content')
    <div class="container">
        <select id="dynamic_select">
            <option value="/compare#18" selected>18th December - 24th December</option>
            <option value="/compare#25">25th December - 31st December</option>
        </select>
        <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>
        <script>
            $(function(){
                // bind change event to select
                $('#dynamic_select').on('change', function () {
                    var url = $(this).val(); // get selected value
                    if (url) { // require a URL
                        window.location = url; // redirect
                    }
                    location.reload();
                    return false;
                });
            });
        </script>
        <div class="days-hours-heatmap">
            <!-- calibration and render type controller -->
            <div class="calibration" role="calibration">
                <div class="group" role="example">
                    <svg width="120" height="17">
                    </svg>
                    <div role="description" class="description">
                        <label>Quiet</label>
                        <label>Loud</label>
                    </div>
                </div>
            </div>
            <svg role="heatmap" class="heatmap"></svg>
        </div>
    </div>

@endsection
