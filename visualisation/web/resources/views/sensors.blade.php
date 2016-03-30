@extends('layouts.app')

@section('content')
<div class="container">
	<div class="row">
		<div class="col-md-10 col-md-offset-1">
			<div class="panel panel-default">
				<div class="panel-heading">Sensors</div>

				<div class="panel-body">
					Here you can view the status of all sensors
					@foreach($sensors as $sensor)
						<div class="panel panel-default">
							<div class="panel-heading">
								<h3 class="panel-title">{{$sensor->name}}</h3>
							</div>
							<div class="panel-body">
								<div class="col-md-4">
									Status: OK
								</div>
								<div class="col-md-8">
									Latest Reading:  {{$sensor->readings()->orderBy('reading_time', 'asc')->first()->value}} at {{$sensor->readings()->orderBy('reading_time', 'asc')->first()->reading_time}}
								</div>
								<div class="col-lg-12">
									Battery:
									<div class="progress">
										<div class="progress-bar" role="progressbar" style="width: {{$sensor->battery}}%">
											{{$sensor->battery}}% remaining
										</div>
									</div>
								</div>
							</div>
						</div>
					@endforeach
				</div>
			</div>
		</div>
	</div>
</div>
@endsection
