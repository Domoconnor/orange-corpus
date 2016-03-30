

@extends('layouts.app')

@section('content')
    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading">Settings</div>
                    <div class="panel-body">
                        {!! Form::model($user, array('url' => '/settings/edit'))!!}
                            <div class="form-group">
                                <label class="col-md-4 control-label">E-Mail Address</label>

                                <div class="col-md-6">
                                    {!! Form::text('email') !!}
                                </div>
                            </div>

                            <div class="form-group">
                                <label class="col-md-4 control-label">Phone</label>

                                <div class="col-md-6">
                                    {!! Form::text('phone') !!}

                                </div>
                            </div>


                            <div class="form-group">
                                <div class="col-md-6 col-md-offset-4">
                                    <button type="submit" class="btn btn-primary">
                                        <i class="fa fa-btn fa-sign-in"></i>Update Settings
                                    </button>

                                </div>
                            </div>
                        {!! Form::close() !!}
                    </div>
                </div>
            </div>
        </div>
    </div>
@endsection
