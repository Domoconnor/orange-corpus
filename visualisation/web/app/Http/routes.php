<?php

/*
|--------------------------------------------------------------------------
| Routes File
|--------------------------------------------------------------------------
|
| Here is where you will register all of the routes in an application.
| It's a breeze. Simply tell Laravel the URIs it should respond to
| and give it the controller to call when that URI is requested.
|
*/

Route::get('/', function () {
    return view('welcome');
});

/*
|--------------------------------------------------------------------------
| Application Routes
|--------------------------------------------------------------------------
|
| This route group applies the "web" middleware group to every route
| it contains. The "web" middleware group is defined in your HTTP
| kernel and includes session state, CSRF protection, and more.
|
*/

Route::group(['middleware' => ['web']], function () {
    //
});

Route::group(['middleware' => 'web'], function () {
    Route::auth();

    Route::get('/home', 'Controller@show_readings');

    Route::get('settings', function()
    {
        return View::make('settings') // pulls app/views/nerd-edit.blade.php
        ->with('user',Auth::user());
    });

    Route::post('settings/edit','Controller@update')->name('settings.edit');

    Route::get('/sensors', 'Controller@sensor');
    Route::get('/readings', 'Controller@show_readings');
    Route::get('/day/{timestamp}', 'Controller@show_day');
    Route::get('/compare', 'Controller@show_compare');

});

Route::post('/api/readings', 'ApiController@readings');

Route::get('/api/get/hourly/{start}/{end}', 'ApiController@get_hourly_averages');
Route::get('/api/get/hourly/', 'ApiController@get_hourly_averages');
Route::get('/api/get', 'ApiController@get_clock_averages');
Route::get('/live', 'Controller@live');



